#include "dialog.h"
#include "ui_dialog.h"
#include <string.h>
#include <stdlib.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16))
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd_h;
QString red2;
QString red1;

char intToHex(int br)
{
    int tmp, i = 0;
    char hex = 0;

    while(br != 0)
    {
        tmp = br % 16;
        if (tmp < 10)
            tmp = tmp + 48;
        else
            tmp = tmp + 55;
        hex += tmp;
        br = br/16;
    }
    return hex;
}

int sati = 0, minuti = 0,sekunde = 0;
char sati_c = 0, minuti_c = 0,sekunde_c = 0;
QTime vreme;

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DANI 0x05
#define MESECI 0x07
#define GODINE 0x08

const char PCF8591=0X51; //adresa
int fd;

unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[7];
                            // sec,min,sat
unsigned char init8563_Store[7]={0x00,0x59,0x08, 0x01, 0x04, 0x10, 0x01};

QString ispis;
QTime time_1;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    if(wiringPiSetup() == -1)
            exit(1);

    fd = wiringPiI2CSetup(PCF8591);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(rtcReadTimeSlot()));

    timer->start(1000);

    time_1.setHMS(0, 0, 0);

    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

}

Dialog::~Dialog()
{
    delete ui;
}
std::string format_s;
std::string tmp;
char *format_c;

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    QString time = arg1;
    QString format =  vreme.toString(time);

    //provera

    format_s = time.toStdString();
    tmp = "hh:mm:ss";

    format_c = &format_s[0];
    //sscanf(format_c, "%c:%c:%c", &sati_c, &minuti_c, &sekunde_c);
    sscanf(format_c, "%d:%d:%d", &sati, &minuti, &sekunde);
    printf("Sati:%x Minuti:%x Sekunde:%x \n", sati, minuti, sekunde);

    sati_c =  (char)sati;
    minuti_c = (char)minuti;
    sekunde_c = (char)sekunde;
    //sati_c =  intToHex(sati);
    //minuti_c = intToHex(minuti);
    //sekunde_c = intToHex(sekunde);

    init8563_Store[2]= sati_c;
    init8563_Store[1]= minuti_c;
    init8563_Store[0]= sekunde_c;

    time_1.setHMS(sati, minuti, sekunde);

}

void Dialog::on_pushButton_clicked()
{
    if (sscanf(format_c, "%d:%d:%d", &sati, &minuti, &sekunde) != 3)
    {
       QMessageBox::warning(this, "Warning", "Invalid format.\n");
    }

    unsigned char i;

   for(i=0;i<=3;i++)
       g8563_Store[i]=init8563_Store[i];

    WriteBuf[0] = SEK;
    WriteBuf[1] = g8563_Store[0];
    wiringPiI2CWriteReg8(fd, SEK, g8563_Store[0]);

    WriteBuf[0] = MIN;
    WriteBuf[1] = g8563_Store[1];
    wiringPiI2CWriteReg8(fd, MIN, g8563_Store[1]);

    WriteBuf[0] = SAT;
    WriteBuf[1] = g8563_Store[2];
    wiringPiI2CWriteReg8(fd, SAT, g8563_Store[2]);

    //inicijalizacija RTC-a
    wiringPiI2CWriteReg8(fd, 0 , 0x00);

    printf("Sati:%d Minuti:%d Sekunde:%d \n", g8563_Store[2], g8563_Store[1], g8563_Store[0]);

}
bool inv;
void Dialog::on_checkBox_clicked(bool checked)
{
    if (checked)
            inv = 1;
    else
        inv = 0;
}

void Dialog::rtcReadTimeSlot()
{

    //QTime time (QTime::currentTime());

    time_1 = time_1.addMSecs(1000);
    QString time_str = time_1.toString();

    unsigned char time[7];
    time[0]=wiringPiI2CReadReg8(fd, SEK);
    time[1]=wiringPiI2CReadReg8(fd, MIN);
    time[2]=wiringPiI2CReadReg8(fd, SAT);


     g8563_Store[0] = time[0] & 0x7f;
     g8563_Store[1] = time[1] & 0x7f;
     g8563_Store[2] = time[2] & 0x3f;


     g8563_Store[0] = changeHexToInt(g8563_Store[0]);
     g8563_Store[1] = changeHexToInt(g8563_Store[1]);
     g8563_Store[2] = changeHexToInt(g8563_Store[2]);


     //string ispis = sati+ ":" + minuti + ":" + sekunde;
     ispis = QString::number(g8563_Store[2]) + ":" +QString::number(g8563_Store[1]) + ":" + QString::number(g8563_Store[0]);
     //vreme (ispis) prebaciti u qstring
     //ui->label_3->setText(ispis);
     //delay(1000);
     //char ispis[10];
     //int sati;
     //sati = atoi(g8563_Store[2]);
     //int minuti;
     //sscanf(g8563_Store[2],"%d", &minuti);
     //int sekunde;
     //sscanf(g8563_Store[2],"%d", &sekunde);

     time_1.setHMS(g8563_Store[2], g8563_Store[1], g8563_Store[0]);
     QString format_1 = time_1.toString();

     ui->label_3->setText(ispis);


         QString red2 = QString::number(g8563_Store[2]) + "h " +QString::number(g8563_Store[1]) + "m";
         QString red1 = QString::number(g8563_Store[0]) + "s";


     lcdClear(lcd_h);
std::string red;
     if (inv)
          red = red1.toStdString();
     else
          red = red2.toStdString();

         char *red_c;

         red_c= &red[0];

         lcdPosition(lcd_h, 0,1);

         lcdPrintf(lcd_h,red_c);
    if (inv)
             red = red2.toStdString();
    else
        red = red1.toStdString();

         red_c= &red[0];

         lcdPosition(lcd_h, 0,0);

         lcdPrintf(lcd_h,red_c);
}




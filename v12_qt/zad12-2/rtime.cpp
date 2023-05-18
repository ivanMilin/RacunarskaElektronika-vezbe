#include "rtime.h"
#include "ui_rtime.h"
const int RS=3;
const int EN=14;
const int D0=4;
const int D1=12;
const int D2=13;
const int D3=6;
int fd;
QString format = "hh:mm:ss";
 const char PCF8563 =0x51;
RTime::RTime(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RTime)
{


    ui->setupUi(this);
    fd=wiringPiI2CSetup(PCF8563);
    P8563_init();
    QTimer *taj = new QTimer(this);
    connect(taj,SIGNAL(timeout()),this,SLOT(P8563_Readtime()));
    taj ->start(1000);

}

RTime::~RTime()
{
    delete ui;
}
#define changeHexToInt(hex) ((((hex)>>4) *10 ) +((hex)%16) )
#define chageIntToHex(int) ((int%10)&(int/10<<4))
//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
unsigned char init8563_Store[3]={0x50,0x59,0x23};




 unsigned char WriteBuf[2];
 unsigned char ReadBuf;
 unsigned char g8563_Store[3];
 // sec,min,sat
 //unsigned char init8563_Store[6]={0x50,0x59,0x23,0x31,0x12,0x22};
void  RTime::P8563_settime()
{
 WriteBuf[0] = SEK;
 WriteBuf[1] = g8563_Store[0];
//bcm2835_i2c_write(WriteBuf,2);
 wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
 WriteBuf[0] = MIN;
 WriteBuf[1] = g8563_Store[1];
 //bcm2835_i2c_write(WriteBuf,2);
wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

 WriteBuf[0] = SAT;
 WriteBuf[1] = g8563_Store[2];
 //bcm2835_i2c_write(WriteBuf,2);
wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
}
void RTime::P8563_init()
{
 unsigned char i;
 for(i=0;i<=6;i++)
 g8563_Store[i]=init8563_Store[i];

 P8563_settime();
 printf("Postavi početno tekuće vreme\n");

//inicijalizacija RTC-a
 WriteBuf[0] = 0x0;
 WriteBuf[1] = 0x00; //normalni rezim rada

 wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

}
void RTime::P8563_Readtime()
{
 int lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
 unsigned char time[7];
time[0]=wiringPiI2CReadReg8(fd,SEK);
time[1]=wiringPiI2CReadReg8(fd,MIN);
time[2]=wiringPiI2CReadReg8(fd,SAT);

 g8563_Store[0] = time[0] & 0x7f;
 g8563_Store[1] = time[1] & 0x7f;
 g8563_Store[2] = time[2] & 0x3f;


 g8563_Store[0] = changeHexToInt(g8563_Store[0]);
 g8563_Store[1] = changeHexToInt(g8563_Store[1]);
 g8563_Store[2] = changeHexToInt(g8563_Store[2]);
 QTime vreme;
 vreme.setHMS(g8563_Store[2],g8563_Store[1],g8563_Store[0]);
 QString format = "hh:mm:ss";
 QString str1 = vreme.toString(format);
 ui->label_3->setText(str1);
 lcdClear(lcd);
  lcdPosition(lcd,0,0);
  lcdPrintf(lcd,"%s",(str1.toStdString()).c_str());

}


void RTime::on_pushButton_clicked()
{

    //char a,b,c;

    QTime vreme = QTime::fromString(ui->lineEdit->QLineEdit::text());
    /*g8563_Store[0] = char(chageIntToHex(vreme.second()));
    g8563_Store[1] = char(chageIntToHex(vreme.minute()));
    g8563_Store[2] = char(chageIntToHex(vreme.hour()));*/
    //a=(unsigned char)vreme.second();
    //b=char(vreme.minute());
    //c=char(vreme.hour());
    g8563_Store[0] = (unsigned char)vreme.second();
    g8563_Store[1] = (unsigned char)(vreme.minute());
    g8563_Store[2] = (unsigned char)(vreme.hour());
    //QString str = vreme.toString(format);
    //P8563_init();

    P8563_settime();
    //ui->label_3->setText(str);
}

void RTime::on_radioButton_clicked()
{
    format = "hh:mm:ss";
}

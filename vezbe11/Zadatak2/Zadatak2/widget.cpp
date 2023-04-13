#include "widget.h"
#include "ui_widget.h"
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>


QString vreme;
QTime temp(QTime::currentTime());
QString format = "hh:mm:ss";
QTime check;

char *red1;
char *red2;

QString red1_p;
QString red2_p;

 int lcd_h;

 const int RS = 3;
 const int EN = 14;
 const int D0 = 4;
 const int D1 = 12;
 const int D2 = 13;
 const int D3 = 6;

 std::string sati;
 std::string minuti;
 std::string sekunde;

 char *sati_c;
 char *minuti_c;
 char *sekunde_c;

 int i;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    if (wiringPiSetup() < 0){
     fprintf (stderr, "Greška pri inicijalizaciji:%s\n", strerror (errno)) ;

    }
     lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
     lcdClear(lcd_h);
   // if(wiringPiSetup() == -1)
      //      exit(1);

      //  fd = wiringPiI2CSetup(PCF8591);

    QTimer *myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this, SLOT(ReadTimeSlot()));
    //connect(myTimer1, SIGNAL(timeout()), this, SLOT(on_checkBox_stateChanged(int arg1));
    myTimer1->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ReadTimeSlot()
{
    QTime vreme(QTime::currentTime());
    temp = temp.addMSecs(1000);
    vreme = temp;

    QString str = vreme.toString(format);

    ui->lineEdit->setText(str);

    std::string red_1_p = str.toStdString();
    sati = str.left(2).toStdString();
    minuti = str.mid(3,2).toStdString();
    sekunde = str.mid(6,2).toStdString();

    sati_c = &sati[0];
    minuti_c = &minuti[0];
    sekunde_c = &sekunde[0];
    //lcdClear(lcd_h);
    if(i)
    {
        lcdClear(lcd_h);
        lcdPosition(lcd_h, 0,0);
        lcdPrintf(lcd_h, sati_c);
        lcdPosition(lcd_h, 4,0);
        lcdPrintf(lcd_h, minuti_c );
        lcdPosition(lcd_h, 8,0);
        lcdPrintf(lcd_h, sekunde_c );
    }
    else
    {
        lcdClear(lcd_h);
        lcdPosition(lcd_h, 0,1);
        lcdPrintf(lcd_h, sati_c);
        lcdPosition(lcd_h, 4,1);
        lcdPrintf(lcd_h, minuti_c );
        lcdPosition(lcd_h, 8,1);
        lcdPrintf(lcd_h, sekunde_c );
    }


   // sscanf(red_1_p,"%s:%s:%s",sati,minuti,sekunde);


}

void Widget::on_pushButton_clicked()
{
    vreme = ui->lineEdit_2->text();
    check = QTime::fromString(vreme, format);

    if(check.isValid())
    {
        temp = QTime::fromString(vreme, format);
        qDebug() << temp;
    }
    else
    {
        QMessageBox::warning(this,"Upozorenje" ,"Pogresan forman. Unesite u obliku hh:mm:ss!");
    }
}

void Widget::on_checkBox_stateChanged(int arg1)
{
    i = arg1;
    qDebug() << arg1;
}

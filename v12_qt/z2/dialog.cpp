#include "dialog.h"
#include "ui_dialog.h"



FILE *log;
FILE *ft;
char tekst[100];
const char NESTO = 0x48;
int fd, adcVal, adcVal_2;
double vr;



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //ui->dial->setDisabled(true);

    wiringPiSetup();
    fd = wiringPiI2CSetup(NESTO);

    QTimer *myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(rtcReadTimeSlot()));
    myTimer -> start(1000);

    log=fopen("log","w");

}

Dialog::~Dialog()
{
    fclose(log);
    delete ui;
}

void Dialog::rtcReadTimeSlot()
{
    //OSVJETLJENJE
        wiringPiI2CReadReg8(fd, NESTO+2);
         adcVal_2 = wiringPiI2CReadReg8(fd, NESTO+2);
         ui->horizontalSlider->setValue(adcVal_2);

//TEMPERATURA
    ft=fopen("/sys/bus/w1/devices/28-000008832b6c/w1_slave","r");
    int i=0;
    for(i=0;i<22;i++) //samo temperatura
        fscanf(ft,"%s", tekst);
    fclose(ft);
    //obrisati „t=”

    for(i=0;i<10;i++) tekst[i]=tekst[i+2];

    int temp=atoi(tekst); //prebaci u double
    double tem=(double)temp/1000;

    ui->lcdNumber->display(tem);

//NAPON
    wiringPiI2CReadReg8(fd, NESTO+3);
    adcVal = wiringPiI2CReadReg8(fd, NESTO+3);
   // vr = ((double)adcVal / 255) * 3.3;

    ui->dial->setValue(adcVal);

}


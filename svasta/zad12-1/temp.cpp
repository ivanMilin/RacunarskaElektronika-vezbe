#include "temp.h"
#include "ui_temp.h"
int fd;
//const char PCF8563 =0x51;
temp::temp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::temp)
{
    ui->setupUi(this);

    //fd=wiringPiI2CSetup(PCF8563);
    //P8563_init();
    QTimer *taj = new QTimer(this);
    connect(taj,SIGNAL(timeout()),this,SLOT(showTemp()));
    taj ->start(1000);
}

temp::~temp()
{
    delete ui;
}


void temp::showTemp()
{
    FILE *ft;
    char tekst[100];
    ft=fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");

    int i=0;
    for(i=0;i<22;i++)
        fscanf(ft,"%s",tekst);
    fclose(ft);
    for(i=0;i<10;i++)
        tekst[i]=tekst[i+2];
    int temp1 =atoi(tekst);
    double tem=(double)temp1/1000;
    ui->lcdNumber->display(tem);




}

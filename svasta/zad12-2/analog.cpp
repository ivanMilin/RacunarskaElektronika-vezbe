#include "analog.h"
#include "ui_analog.h"
const char PCF8591 = 0x48;
int fd;
analog::analog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::analog)
{
    wiringPiSetup();
    fd=wiringPiI2CSetup(PCF8591);
    ui->setupUi(this);
    QTimer *taj = new QTimer(this);
    connect(taj,SIGNAL(timeout()),this,SLOT(showVals()));
    taj ->start(1000);
}

analog::~analog()
{
    delete ui;
}

void analog::showVals()
{
    int napon,osvetljaj,temp;
    napon=wiringPiI2CReadReg8(fd, PCF8591 + 3) ;//napon
    osvetljaj=wiringPiI2CReadReg8(fd, PCF8591 + 2) ;//osvetljaj
    temp=wiringPiI2CReadReg8(fd, PCF8591 + 0) ;//temp
    napon=(double)napon;
    //adc1=(double)adc2/256*50;
    temp=(double)temp;
    osvetljaj=(double)osvetljaj;
    ui->dial->setDisabled(true);
    ui->dial->setValue(napon);
    ui->lcdNumber->setDisabled(true);
    ui->lcdNumber->display(temp);
    ui->verticalSlider->setDisabled(true);
    ui->verticalSlider->setValue(osvetljaj);
;}

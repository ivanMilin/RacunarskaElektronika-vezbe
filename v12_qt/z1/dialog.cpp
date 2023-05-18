#include "dialog.h"
#include "ui_dialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QTime>

FILE *log;
FILE *ft;
char tekst[100];

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


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

}


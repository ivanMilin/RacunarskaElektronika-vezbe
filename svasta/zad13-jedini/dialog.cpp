#include "dialog.h"
#include "ui_dialog.h"
const char PCF8591 = 0x48;
QT_CHARTS_USE_NAMESPACE
int fd;
int adcVal;
int del=0;
int t;
QLineSeries *series;
QChart *chart;
QChartView *chartView;
QTimer *myTimer1;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    fd = wiringPiI2CSetup(PCF8591);

    myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this,
        SLOT(ReadYL40()));
    series=new QLineSeries();


    chart=new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setMin(0);
    chart->axisX()->setMax(5);
    chart->axisY()->setRange(0,3.3);
    chart->setTitle("Merenje napona");
    chartView =new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::ReadYL40()
{
    wiringPiI2CReadReg8(fd,PCF8591+3);
    adcVal=wiringPiI2CReadReg8(fd,PCF8591+3)*3.3/255;
    if(del)
    {
        del=0;
        t=0;
        series->clear();
    }
    if(t==6)
    {
        t=0;
        series->clear();
    }
    series->append(t,adcVal);
    t++;
    chartView->update();
}

void Dialog::on_pushButton_2_clicked()
{
    del=1;
}

void Dialog::on_pushButton_clicked()
{
    myTimer1->start(1000);

}

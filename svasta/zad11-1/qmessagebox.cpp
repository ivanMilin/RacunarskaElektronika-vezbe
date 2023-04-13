#include "qmessagebox.h"
#include "ui_qmessagebox.h"

QMessageBox::QMessageBox(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QMessageBox)
{
    wiringPiSetup();
    ui->setupUi(this);

}

QMessageBox::~QMessageBox()
{
    delete ui;
}

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

void QMessageBox::on_pushButton_clicked()
{
   int lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
    pinMode(25,OUTPUT);
    digitalWrite(25, HIGH);

}

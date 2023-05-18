#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <string.h>

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd_h;
QString red2;
QString red1;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    if (wiringPiSetup() < 0){
        fprintf (stderr, "Greška pri inicijalizaciji:%s\n", strerror(errno)) ;
    }
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_lineEdit_textChanged(const QString &arg1)
{

    red2 = arg1;

}

void Dialog::on_lineEdit_2_textChanged(const QString &arg1)
{

    red1 = arg1;

}

void Dialog::on_pushButton_clicked(bool checked)
{
    if (checked)
    {
        lcdClear(lcd_h);

        std::string red = red2.toStdString();
        char *red_c;

        red_c= &red[0];

        lcdPosition(lcd_h, 0,1);

        lcdPrintf(lcd_h,red_c);

        red = red1.toStdString();

        red_c= &red[0];

        lcdPosition(lcd_h, 0,0);

       lcdPrintf(lcd_h,red_c);

    }
}

void Dialog::on_pushButton_clicked()
{
    lcdClear(lcd_h);

    std::string red = red2.toStdString();
    char *red_c;

    red_c= &red[0];

    lcdPosition(lcd_h, 0,1);

    lcdPrintf(lcd_h,red_c);

    red = red1.toStdString();

    red_c= &red[0];

    lcdPosition(lcd_h, 0,0);

   lcdPrintf(lcd_h,red_c);
}

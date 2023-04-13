#include "widget.h"
#include "ui_widget.h"

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
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    red1_p = arg1;




}



void Widget::on_lineEdit_returnPressed()
{
     //on_lineEdit_textChanged(red1);

}

void Widget::on_lineEdit_2_textChanged(const QString &arg1)
{
     red2_p = arg1;



}

void Widget::on_pushButton_clicked()
{
    std::string red_1_p = red1_p.toStdString();

    red1 = &red_1_p[0];

    std::string red_2_p = red2_p.toStdString();

    red2 = &red_2_p[0];

    //delay(400);
    lcdPosition(lcd_h, 0,1);
    lcdPrintf(lcd_h, red2 );
    lcdPosition(lcd_h, 0,0);
    lcdPrintf(lcd_h, red1 );
}

void Widget::on_pushButton_pressed()
{

}

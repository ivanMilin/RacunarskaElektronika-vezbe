#include "fourtoggle.h"
#include "ui_fourtoggle.h"

fourtoggle::fourtoggle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fourtoggle)
{
    ui->setupUi(this);
}

fourtoggle::~fourtoggle()
{
    delete ui;
}
int vr1=LOW;
int vr2=LOW;
int vr3=LOW;
int vr4=LOW;
void fourtoggle::on_pushButton_3_clicked()
{
    vr1=~vr1;
    digitalWrite(25,vr1);
}

void fourtoggle::on_pushButton_2_clicked()
{
    vr2=~vr2;
    digitalWrite(26,vr2);
}

void fourtoggle::on_pushButton_clicked()
{
    vr3=~vr3;
    digitalWrite(27,vr3);
}

void fourtoggle::on_pushButton_4_clicked()
{
    vr4=~vr4;
    digitalWrite(28,vr4);
}

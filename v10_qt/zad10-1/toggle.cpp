#include "toggle.h"
#include "ui_toggle.h"

toggle::toggle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::toggle)
{
    ui->setupUi(this);
}

toggle::~toggle()
{
    delete ui;
}

int vrednost=LOW;
void toggle::on_pushButton_clicked()
{

    if(vrednost==HIGH)
    {vrednost=LOW;}
    else if(vrednost==LOW)
    {vrednost=HIGH;}
    digitalWrite(25,vrednost);
}

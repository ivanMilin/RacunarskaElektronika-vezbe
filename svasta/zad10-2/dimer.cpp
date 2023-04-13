#include "dimer.h"
#include "ui_dimer.h"

dimer::dimer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dimer)
{
    ui->setupUi(this);
}

dimer::~dimer()
{
    delete ui;
}


void dimer::on_horizontalSlider_valueChanged(int value)
{
    softPwmWrite(28, value);
}

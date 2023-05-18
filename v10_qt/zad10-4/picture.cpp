#include "picture.h"
#include "ui_picture.h"

picture::picture(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::picture)
{
    ui->setupUi(this);
}

picture::~picture()
{
    delete ui;
}
QPixmap image1("/home/pi/skala_krunic/zad10-4/on.jpeg");
QPixmap image2("/home/pi/skala_krunic/zad10-4/off.jpeg");
void picture::on_pushButton_clicked(bool checked)
{

    if(checked==true)
    {
        ui->label->setPixmap(image1);

    }
    else
    {
        ui->label->setPixmap(image2);

    }
    ui->label->show();
}

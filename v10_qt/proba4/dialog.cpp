#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked(bool checked)
{
    QPixmap on(":/resources/slike/slike/on.jpg");
    QPixmap off(":/resources/slike/slike/off.jpg");

    if (checked)
        ui->label->setPixmap(on);
    else
        ui->label->setPixmap(off);

    ui->label->show();
}

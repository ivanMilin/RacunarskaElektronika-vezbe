#ifndef PICTURE_H
#define PICTURE_H

#include <QDialog>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QPixmap>
#include <QApplication>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class picture; }
QT_END_NAMESPACE

class picture : public QDialog
{
    Q_OBJECT

public:
    picture(QWidget *parent = nullptr);
    ~picture();

private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::picture *ui;
};
#endif // PICTURE_H

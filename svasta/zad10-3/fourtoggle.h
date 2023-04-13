#ifndef FOURTOGGLE_H
#define FOURTOGGLE_H

#include <QDialog>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
QT_BEGIN_NAMESPACE
namespace Ui { class fourtoggle; }
QT_END_NAMESPACE

class fourtoggle : public QDialog
{
    Q_OBJECT

public:
    fourtoggle(QWidget *parent = nullptr);
    ~fourtoggle();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::fourtoggle *ui;
};
#endif // FOURTOGGLE_H

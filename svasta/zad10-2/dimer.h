#ifndef DIMER_H
#define DIMER_H

#include <QDialog>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
QT_BEGIN_NAMESPACE
namespace Ui { class dimer; }
QT_END_NAMESPACE

class dimer : public QDialog
{
    Q_OBJECT

public:
    dimer(QWidget *parent = nullptr);
    ~dimer();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::dimer *ui;
};
#endif // DIMER_H

#ifndef DIALOG_H
#define DIALOG_H
//#include "ui_dialog.h"
#include <QDialog>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QTimer>
#include <QTime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public slots:
    void rtcReadTimeSlot();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

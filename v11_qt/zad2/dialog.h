#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <stdio.h>

#include <lcd.h>
#include <wiringPi.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();
    void rtcReadTimeSlot();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

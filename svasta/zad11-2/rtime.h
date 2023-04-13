#ifndef RTIME_H
#define RTIME_H
#include <QDialog>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>
#include <QDialog>
#include <QTime>
#include <QTimer>
#include <wiringPiI2C.h>

QT_BEGIN_NAMESPACE
namespace Ui { class RTime; }
QT_END_NAMESPACE

class RTime : public QDialog
{
    Q_OBJECT

public:
    RTime(QWidget *parent = nullptr);
    ~RTime();

private slots:
    //void showTime(QTime vreme);
    void on_pushButton_clicked();
    void P8563_settime();
    void P8563_init();
    void P8563_Readtime();

    void on_radioButton_clicked();

private:
    Ui::RTime *ui;
};
#endif // RTIME_H

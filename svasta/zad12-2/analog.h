#ifndef ANALOG_H
#define ANALOG_H
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>
#include <QDialog>
#include <QTime>
#include <QTimer>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <sys/fcntl.h>


QT_BEGIN_NAMESPACE
namespace Ui { class analog; }
QT_END_NAMESPACE

class analog : public QDialog
{
    Q_OBJECT

public:
    analog(QWidget *parent = nullptr);
    ~analog();
private slots:
      void showVals();
private:
    Ui::analog *ui;
};
#endif // ANALOG_H

#ifndef TEMP_H
#define TEMP_H
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
namespace Ui { class temp; }
QT_END_NAMESPACE

class temp : public QDialog
{
    Q_OBJECT

public:
    temp(QWidget *parent = nullptr);
    ~temp();

private slots:
      void showTemp();
private:
    Ui::temp *ui;
};
#endif // TEMP_H

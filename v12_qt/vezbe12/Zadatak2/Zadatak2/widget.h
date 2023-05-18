#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <wiringPi.h>
#include <lcd.h>


#define changeHexToInt(hex) ((((hex)>>4) *10 ) +((hex)%16) )

#define changeIntToHex(hex) ((hex % 10) & ((hex / 10 )<< 4))

//adrese registara
#define SEK 0x02
#define MIN1 0x03
#define SAT 0x04

void P8563_Settime();

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void ReadTimeSlot();

private slots:


    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <wiringPi.h>
#include <lcd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_lineEdit_returnPressed();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

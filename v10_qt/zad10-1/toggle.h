#ifndef TOGGLE_H
#define TOGGLE_H

#include <QDialog>
#include <wiringPi.h>
#include <stdio.h>
QT_BEGIN_NAMESPACE
namespace Ui { class toggle; }
QT_END_NAMESPACE

class toggle : public QDialog
{
    Q_OBJECT

public:
    toggle(QWidget *parent = nullptr);
    ~toggle();

private slots:
    void on_pushButton_clicked();

private:
    Ui::toggle *ui;
};
#endif // TOGGLE_H

#ifndef DIALOG_H
#define DIALOG_H
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE
#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include<QTimer>
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
    void ReadYL40();
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

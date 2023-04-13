#ifndef QMESSAGEBOX_H
#define QMESSAGEBOX_H

#include <QDialog>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class QMessageBox; }
QT_END_NAMESPACE

class QMessageBox : public QDialog
{
    Q_OBJECT

public:
    QMessageBox(QWidget *parent = nullptr);
    ~QMessageBox();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QMessageBox *ui;
};
#endif // QMESSAGEBOX_H

#include "dimer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    wiringPiSetup ();
    pinMode(25, PWM_OUTPUT);
    softPwmCreate(28,0,100);
    QApplication a(argc, argv);
    dimer w;
    w.show();
    return a.exec();
}

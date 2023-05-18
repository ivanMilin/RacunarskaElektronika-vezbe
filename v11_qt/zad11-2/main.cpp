#include "rtime.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    wiringPiSetup();

    QApplication a(argc, argv);
    RTime w;
    w.show();
    return a.exec();
}

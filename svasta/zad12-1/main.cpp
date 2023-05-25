#include "temp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
     //wiringPiSetup();
    QApplication a(argc, argv);
    temp w;
    w.show();
    return a.exec();
}

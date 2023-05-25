#include "analog.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    analog w;
    w.show();
    return a.exec();
}

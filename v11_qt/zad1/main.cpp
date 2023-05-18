#include "dialog.h"
#include <lcd.h>

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();



    //lcdPosition(lcd_h, 0,1);
    //lcdPrintf(lcd_h, "u 2 reda");

    //delay(2000);

    //lcdClear(lcd_h);

    return a.exec();
}

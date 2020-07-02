#include "sensor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sensor w;
    w.show();
    return a.exec();
}

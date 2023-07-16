#include "Widget.h"
#include "Device.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window1;
    Device* device = new Device();
    device->show();

    return a.exec();
}

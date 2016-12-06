#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    
    return a.exec();
}
//LIBS += -L./hwlib -lcamera_interface
//LIBS += -L ./hwlib -lshm

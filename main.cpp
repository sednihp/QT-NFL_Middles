#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setGeometry(100,200,w.width(),w.height());
    w.show();
    return a.exec();
}

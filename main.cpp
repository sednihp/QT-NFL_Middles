#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NFLMiddle nflMiddle;
    nflMiddle.setGeometry(100, 200, nflMiddle.width(), nflMiddle.height());
    nflMiddle.show();

    return a.exec();
}

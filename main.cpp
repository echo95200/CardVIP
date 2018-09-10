#include "mainwindow.h"
#include "cartevip.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    CarteVIP *c = new CarteVIP();
    if (c->initConnectDatabase())
        c->show();

    return a.exec();
}

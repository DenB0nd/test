#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow(QHostAddress::LocalHost, 2345);
    w->show();
    return a.exec();
}

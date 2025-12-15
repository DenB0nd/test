#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow(QHostAddress::LocalHost, 1234);
    w->show();
    a.exec();
    return 0;
}

#include "udplistener.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    UdpListener* listener = new UdpListener(QHostAddress::LocalHost, 1234);

    return app.exec();
}



#include "tcplistener.h"

#include <QDebug>
#include <QCoreApplication>

TcpListener::TcpListener(QHostAddress address, quint16 port, QObject *parent)
    : QObject(parent)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection, this, &TcpListener::processNewConnection);

    if(!tcpServer->listen(address, port)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void TcpListener::processNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();

    tcpSocket->write("Hello, World!!! I am echo server!\r\n");

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(processClientDisconnection()));
}

void TcpListener::readMessage()
{
    QByteArray array;
    while(tcpSocket->bytesAvailable()>0)
    {
        array.append(tcpSocket->readAll());
    }
    emit messageRecieved(QString(array));
}

void TcpListener::processClientDisconnection()
{
    tcpSocket->close();
}

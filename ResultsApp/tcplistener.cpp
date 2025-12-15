#include "tcplistener.h"

#include <QDebug>
#include <QCoreApplication>

TcpListener::TcpListener(QHostAddress address, quint16 port, QObject *parent)
    : QObject(parent)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection, this, &TcpListener::processNewConnection);

    if(!tcpServer->listen(address, port)){
        qDebug() << "Сервер не запущен";
    } else {
        qDebug() << "Сервер запущен";
    }
}

void TcpListener::processNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();

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

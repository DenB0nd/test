#include "tcpclient.h"

TcpClient::TcpClient(QHostAddress address, quint16 port, QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);
    socket->connectToHost(address, port);
}

void TcpClient::sendMessage(QString message)
{
    if(socket->isOpen())
    {
        socket->write(message.toUtf8());
    }
}

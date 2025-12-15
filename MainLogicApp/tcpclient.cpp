#include "tcpclient.h"

TcpClient::TcpClient(QHostAddress address, quint16 port, QObject *parent)
    : QObject{parent}, address(address), port(port)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(address, port);
}

void TcpClient::sendMessage(QString message)
{
    socket->connectToHost(address, port);
    if(socket->isOpen())
    {
        socket->write(message.toUtf8());
    }
}

#include "udpservice.h"

UdpService::UdpService(QHostAddress address, quint16 port, QObject *parent) :
    address(address),
    port(port){}

UdpService::~UdpService()
{
    delete udpSocket;
}

void UdpService::sendStartMessage(int value)
{
    sendMessage(startMessage + ":" + QString::number(value));
}

void UdpService::sendStopMessage(int value)
{
    sendMessage(stopMessage+ ":" + QString::number(value));
}

void UdpService::sendRemoveMessage(int value)
{
    sendMessage(removeMessage + ":" + QString::number(value));
}

void UdpService::sendMessage(QString message)
{
    qDebug() << message;
    QByteArray data = message.toUtf8();
    udpSocket->writeDatagram(data, address, port);
}

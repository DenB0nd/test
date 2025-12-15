#ifndef UDPSERVICE_H
#define UDPSERVICE_H

#include <QUdpSocket>
#include <QDebug>

class UdpService : public QObject {
    Q_OBJECT

public:
    explicit UdpService(QHostAddress address, quint16 port, QObject *parent = nullptr);
    ~UdpService();

    void sendStartMessage(int value);
    void sendStopMessage(int value);
    void sendRemoveMessage(int value);

private:
    QHostAddress address;
    quint16 port;
    QUdpSocket* udpSocket = new QUdpSocket();
    const QString startMessage = QString("start");
    const QString stopMessage = QString("stop");
    const QString removeMessage = QString("remove");
    void sendMessage(QString message);
};

#endif // UDPSERVICE_H

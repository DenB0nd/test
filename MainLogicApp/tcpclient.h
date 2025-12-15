#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

// класс, отвечающий за общений MainLogicApp и ResultsApp по Tcp (клиент)
class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QHostAddress address, quint16 port, QObject *parent = nullptr);
    void sendMessage(QString message);
private:
    QTcpSocket* socket;
    QHostAddress address;
    quint16 port;
};

#endif // TCPCLIENT_H

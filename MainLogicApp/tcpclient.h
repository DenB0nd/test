#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

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

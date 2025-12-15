#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>


class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QHostAddress address, quint16 port, QObject *parent = nullptr);
    void sendMessage(QString message);
private:
    QTcpSocket* socket;
};

#endif // TCPCLIENT_H

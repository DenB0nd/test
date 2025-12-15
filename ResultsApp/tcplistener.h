#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpListener : public QObject
{
    Q_OBJECT
public:
    explicit TcpListener(QHostAddress address, quint16 port, QObject *parent = 0);

public slots:
    void processNewConnection();
    void readMessage();
    void processClientDisconnection();

signals:
    void messageRecieved(QString message);

private:
    QTcpServer * tcpServer;
    QTcpSocket * tcpSocket;
};

#endif // TCPLISTENER_H

#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include "reader.h"
#include "tcpclient.h"
#include "writer.h"

#include <QHostAddress>
#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include <QThread>

#include <vector>
#include <memory>

class UdpListener : public QObject
{
    Q_OBJECT
public:
    explicit UdpListener(QHostAddress address, quint16 port, QObject *parent = nullptr);

public slots:
    void sendMessage(QString message);

signals:
    void stopAlgorithm();

private:
    QHostAddress address;
    quint16 port;
    QUdpSocket* udpSocket = new QUdpSocket();
    TcpClient* client = new TcpClient(QHostAddress::LocalHost, 2345);
    Writer* writer;
    Reader* reader;
    QThread* writerThread = new QThread;
    QThread* readerThread = new QThread;
    // для контейнера выбран вектор так как для записи в случайное место контейнера требуется быстрый произвольный доступ по индексу
    // у вектора это О(1)
    // также мы знаем изначальный размер вектора, следовательно не будет дополнительных расходов при вставке элемента
    // следовательно запись / чтение N элементов по произвольному индексу будут O(N)
    std::shared_ptr<std::vector<double>> container;

    void readPendingDatagrams();
    void processMessage(QString message);
    void startAlgorithm(int N);
    void removeElements(int N);
};

#endif // UDPLISTENER_H

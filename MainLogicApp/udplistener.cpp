#include "udplistener.h"
#include <QThread>
UdpListener::UdpListener(QHostAddress address, quint16 port, QObject *parent)
    : QObject{parent}
{
    if (!udpSocket->bind(address, port))
    {
        qDebug() << "Failed to bind to port" << port << ": " << udpSocket->errorString();
    }
    else
    {
        qDebug() << "Binded";
    }
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpListener::readPendingDatagrams);
}

// читаем сообщение от SettingsApp
void UdpListener::readPendingDatagrams()
{
    QByteArray buffer;
    buffer.resize(udpSocket->pendingDatagramSize());

    udpSocket->readDatagram(buffer.data(), buffer.size(), &address, &port);
    QString message = QString::fromUtf8(buffer);
    qDebug() << message << "\n";
    processMessage(message);
}

// обрабатываем сообщение
void UdpListener::processMessage(QString message)
{
    QStringList tokens = message.split(":");
    if (tokens.size() < 2)
    {
        qDebug() << "Неправильный формат: недостаточно токенов";
        return;
    }

    bool ok;
    int N = tokens[1].toInt(&ok);
    if (!ok)
    {
        qDebug() << "Неправильный формат: N не является числом";
        return;
    }

    auto command = tokens[0];
    if (command == "start"){
        startAlgorithm(N);
    } else if (command == "stop") {
        emit stopAlgorithm();
    } else if (command == "remove"){
        removeElements(N);
    } else {
        qDebug() << "Неправильный формат: неизвестеная команда " << command;
    }
}

// запуск алгоритма
void UdpListener::startAlgorithm(int N)
{
    container = std::make_shared<std::vector<double>>(N);
    // создаём поток для записи
    writerThread = new QThread;
    writer = new Writer(container, this);
    writer->moveToThread(writerThread);
    // создаём поток для чтения
    readerThread = new QThread;
    reader = new Reader(container, this);
    reader->moveToThread(readerThread);

    // связывем запуск записи с запуском потока записи
    connect(writerThread, SIGNAL(started()), writer, SLOT(process()));
    // связывем чтение с добавлением записи
    connect(writer, SIGNAL(elementAdded(int)), reader, SLOT(process(int)));
    // связываем старт алгоритма с отправкой сообшения
    connect(writer, SIGNAL(started(QString)), this, SLOT(sendMessage(QString)));
    connect(reader, SIGNAL(started(QString)), this, SLOT(sendMessage(QString)));
    // связываем окончание алгоритма с отправкой сообщения для ResultsApp
    connect(reader, SIGNAL(finished(QString)), this, SLOT(sendMessage(QString)));
    connect(writer, SIGNAL(finished(QString)), this, SLOT(sendMessage(QString)));
    // данные сигналы требуются для корректного завершения работы
    connect(writer, SIGNAL(finished(QString)), writerThread, SLOT(quit()));
    connect(writerThread, SIGNAL(finished()), writerThread, SLOT(deleteLater()));
    connect(reader, SIGNAL(finished(QString)), readerThread, SLOT(quit()));
    connect(readerThread, SIGNAL(finished()), readerThread, SLOT(deleteLater()));
    connect(this, SIGNAL(stopAlgorithm()), readerThread, SLOT(quit()));
    connect(this, SIGNAL(stopAlgorithm()), writerThread, SLOT(quit()));


    // запускаем потоки
    writerThread->start();
    readerThread->start();
}


// убираем N элементов, не изменяя фактический размер коллекции
void UdpListener::removeElements(int N)
{
    emit stopAlgorithm();
    if (N >= container->size())
    {
        container->clear();
    }
    else
    {
        container->resize(container->size() - N);
    }
}

// отправляем сообщение на ResultsApp
void UdpListener::sendMessage(QString message)
{
    qDebug() << message;
    client->sendMessage(message);
}

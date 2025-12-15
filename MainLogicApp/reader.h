#ifndef READER_H
#define READER_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <vector>
#include <numeric>
#include <random>
#include <chrono>

// класс отвечающй за чтение элемента и контейнера
class Reader : public QObject
{
    Q_OBJECT

public:
    Reader(std::shared_ptr<std::vector<double>> container, QObject *parent = nullptr);

    QString pid;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

public slots:
    void process(int index);

signals:
    // события начала и конца, требуются для отправки сообщений к ResultsApp
    void started(QString message);
    void finished(QString message);

private:
    std::shared_ptr<std::vector<double>> container;
    int counter = 0;
};

#endif // READER_H

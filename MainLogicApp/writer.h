#ifndef WRITER_H
#define WRITER_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

// класс, отвечающий за запись элементов в контейнер
class Writer : public QObject
{
    Q_OBJECT

public:
    Writer(std::shared_ptr<std::vector<double>> container, QObject *parent = nullptr);

    QString pid;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

public slots:
    void process();

signals:
    // события начала и конца, требуются для отправки сообщений к ResultsApp
    void started(QString message);
    void finished(QString message);
    // событие добавление элемента, требуется для обработки в Reader
    void elementAdded(int index);

private:
    std::shared_ptr<std::vector<double>> container;
};

#endif // WRITER_H

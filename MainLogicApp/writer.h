#ifndef WRITER_H
#define WRITER_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

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
    void started(QString message);
    void elementAdded(int index);
    void finished(QString message);

private:
    std::shared_ptr<std::vector<double>> container;
};

#endif // WRITER_H

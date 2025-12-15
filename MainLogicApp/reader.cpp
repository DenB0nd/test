#include "reader.h"

#include <QThread>
#include <unistd.h>

Reader::Reader(std::shared_ptr<std::vector<double>> container, QObject *parent):
    container(container){}

// обрабатываем сигнал добавления элемента
void Reader::process(int index)
{
    if (pid == nullptr)
    {
        QTextStream(&pid) << QThread::currentThreadId();
        qDebug() << "reader: " << pid;
        start = std::chrono::steady_clock::now();
        emit started("Reading started. Reader pid: " + pid + "\n");
    }
    double value = container->at(index);
    qDebug() << "reader " << index << " : " << value;
    counter++;
    if (counter >= container->size())
    {
        end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        auto str = QString::number(duration);
        emit finished("Reader finished. Execution time: " + str + "ms\n");
    }
}

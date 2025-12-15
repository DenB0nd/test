#include "writer.h"

Writer::Writer(std::shared_ptr<std::vector<double>> container, QObject *parent):
    container(container){}

void Writer::process()
{
    if (pid == nullptr)
    {
        start = std::chrono::steady_clock::now();
        QTextStream(&pid) << QThread::currentThreadId();
        qDebug() << "writer: " << pid;
        emit started("Writing started. Writing pid: " + pid + "\n");
    }
    auto N = container->size();
    // генерируем вектор индексов и перемешиваем его для обеспечения случайного доступа к вектору по индексу
    std::vector<int> indeces(N);
    std::iota(indeces.begin(), indeces.end(), 0);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::shuffle(indeces.begin(), indeces.end(), generator);
    std::uniform_real_distribution<double> distribution(-100, 100);

    // для каждого индекса генерируем случайный double
    for(int index : indeces)
    {
        double value = distribution(generator);
        // в данной реализации mutex не нужен потому что считывающий поток читает значение всегда после записывающего
        // и каждый раз новый элемент добавляется в уникальную ячейку контейнера
        container->at(index) = value;
        // сигнализируем о том, что добавили элемент
        emit elementAdded(index);
        qDebug() << "writer " << index << " : " << value;
    }
    end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto str = QString::number(duration);
    emit finished("Writer finished. Execution time: " + str + "ms\n");
}

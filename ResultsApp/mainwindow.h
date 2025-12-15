#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcplistener.h"

#include <QListView>
#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QHostAddress address, quint16 port, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateView(QString message);

private:
    Ui::MainWindow *ui;
    QListView *listView;
    QStringListModel *model;
    QStringList items;
    TcpListener* tcpListener;

    void defineLayout();
};
#endif // MAINWINDOW_H

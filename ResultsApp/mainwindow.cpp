#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QHostAddress address, quint16 port, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    defineLayout();
    tcpListener = new TcpListener(address, port);
    connect(tcpListener, TcpListener::messageRecieved, this, MainWindow::updateView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// устанавливаем лейаут приложения
void MainWindow::defineLayout()
{
    setWindowTitle("Results");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    listView = new QListView(centralWidget);
    model = new QStringListModel(items, this);
    listView->setModel(model);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(listView);


    centralWidget->setLayout(layout);
}

void MainWindow::updateView(QString message)
{
    items.append(message);
    model->setStringList(items);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QHostAddress address, quint16 port, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpService = new UdpService(address, port, this);
    defineLayout();
    loadSettings();
}

// устанавливаем лейаут приложения
void MainWindow::defineLayout()
{
    setWindowTitle("Settings");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QLabel *label = new QLabel("N");

    spinBox = new QSpinBox();
    spinBox->setRange(0, MAX_N);

    QPushButton *startButton = new QPushButton("Start");
    QPushButton *stopButton = new QPushButton("Stop");
    QPushButton *removeButton = new QPushButton("Remove");

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(label);
    horizontalLayout->addWidget(spinBox);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addLayout(horizontalLayout);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);
    layout->addWidget(removeButton);

    //подключаем сигналы к слотам
    connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClicked()));
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartButtonClicked()
{
    udpService->sendStartMessage(spinBox->value());
}

void MainWindow::onStopButtonClicked()
{
    udpService->sendStopMessage(spinBox->value());
}

void MainWindow::onRemoveButtonClicked()
{
    udpService->sendRemoveMessage(spinBox->value());
}

void MainWindow::onSpinBoxValueChanged(int value)
{
    saveSettings();
}

// загрузка настрок
void MainWindow::loadSettings()
{
    bool ok;
    int n = settings->value("N").toInt(&ok);
    if (ok)
    {
        spinBox->setValue(n);
    }
    else
    {
        spinBox->setValue(0);
    }

}

// сохранение настроек
void MainWindow::saveSettings()
{
    settings->setValue("N", spinBox->value());
}

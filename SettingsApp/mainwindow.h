#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "udpservice.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QDebug>

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
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onRemoveButtonClicked();
    void onSpinBoxValueChanged(int value);
private:
    Ui::MainWindow *ui;
    UdpService* udpService;

    const int MAX_N = 100000;
    QSettings* settings = new QSettings("./config.ini", QSettings::IniFormat);
    QSpinBox *spinBox;

    void defineLayout();
    void loadSettings();
    void saveSettings();
};
#endif // MAINWINDOW_H

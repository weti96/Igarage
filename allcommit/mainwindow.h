#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QStandardItemModel>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QSerialPort>
#include <QMessageBox>
#include "setserial.h"
#include "icread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    qint32 SNumber;

private:
    Ui::MainWindow *ui;
    SetSerial *settings;
    QSerialPort *serial;
    QLabel *status;
    IcRead *ICshow;

private slots:
    void On_About();
    void Set_Pic();
    void Serial_Open();
    void Personal_OP();
    void IcShow();

    void closeSerialPort();
    void showStatusMessage(const QString &message);
    void readData();
    void writeData(const QByteArray &data);
    void handleError(QSerialPort::SerialPortError error);
};

#endif // MAINWINDOW_H

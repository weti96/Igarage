#ifndef SETSERIAL_H
#define SETSERIAL_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QStatusBar>
#include <QDebug>
#include <QDialog>
#include <QIntValidator>
namespace Ui {
class SetSerial;
}

class SetSerial : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    explicit SetSerial(QWidget *parent = 0);
    ~SetSerial();
    Settings settings() const;

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SetSerial *ui;
    Settings currentSettings;
    QIntValidator *intValidator;
};


#endif // SETSERIAL_H

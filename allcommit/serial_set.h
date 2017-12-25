#ifndef SERIAL_SET_H
#define SERIAL_SET_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>
#include <QtSerialBus/QCanBus>
#include <QWriteLocker>
#include <QtCore/QReadLocker>
#include <QtCore/QWriteLocker>

#define TIME_OUT 10
struct PortSettings
{
    long Timeout_Millisec;
};
namespace Ui {
class Serial_Set;
}

class Serial_Set : public QMainWindow
{
    Q_OBJECT

public:
    explicit Serial_Set(QWidget *parent = 0);
    ~Serial_Set();
private:
    Ui::Serial_Set *ui;

    QLabel *m_pStatusLbl;
    QLabel *m_pRxCountLbl;
    QLabel *m_pTxCountLbl;
    QPushButton *m_pClearCountBtn;
    QSerialPort *m_pUserUart;
    uint32_t m_uiRxByteCounter = 0;
    uint32_t m_uiTxByteCounter = 0;
    uint32_t m_uiMaxRcvBuff = 0;
    PortSettings settings;

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

private:
    void __UartStateSwitch(bool stats);
    Settings currentSettings;


private slots:
    void set_baud(QSerialPort::BaudRate);
    void __OnOpenBtnClicked();
    void __OnReadUserUart();
    void __OnClearCountBtnClicked();
    void __OnSendBtnClicked();
    //void __OnRcvClrBtnClicked();
    void __OnMaxRcvBuffLEditChanged(QString);
    void __OnRxTxtEditTEditChanged();
};

#endif // SERIAL_SET_H

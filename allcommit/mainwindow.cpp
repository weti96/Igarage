#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "setserial.h"
#include "icread.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString title=QString::fromLocal8Bit("立体车库");
    this->setWindowTitle(title);
    QImage *img=new QImage;
    if(!(img->load("F:/Project 2/allcommit/20170728150155.jpg")))
        qDebug()<<"cann't load!";
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(*img));
    //! [1]
    //!
        serial = new QSerialPort(this);
        settings = new SetSerial;
        status = new QLabel;
        ui->statusBar->addWidget(status);
        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &MainWindow::handleError);


    QObject::connect(ui->actionPic,SIGNAL(triggered(bool)),this,SLOT(Set_Pic()));
    QObject::connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(On_About()));
    QObject::connect(ui->AboutButton,SIGNAL(clicked(bool)),this,SLOT(On_About()));
    QObject::connect(ui->ICButton,SIGNAL(clicked(bool)),settings,SLOT(show()));
    connect(ui->ConnectAct,SIGNAL(triggered(bool)),this,SLOT(Personal_OP()));
    connect(ui->actionDisconnect,SIGNAL(triggered(bool)),this,SLOT(closeSerialPort()));
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(serial,&QSerialPort::readyRead,this,&MainWindow::IcShow);
    //connect(console, &Console::getData, this, &MainWindow::writeData);
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::On_About()
{
    About my;
    my.exec();
}

void MainWindow::Set_Pic()
{
    QString filename;
    QImage *img=new QImage;
    filename=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择图片"),"","*.jpg *.png");
    if(filename.isEmpty()||filename.isNull())
    {
        QMessageBox::information(this,"Error","The filename is empty,Please choose again.");
    }
    else{
    img->load(filename);
    ui->label->setPixmap(QPixmap::fromImage( *img));
    }
}

void MainWindow::Serial_Open()
{
    SetSerial w;
    w.exec();
}

void MainWindow::Personal_OP()
{
    //IcRead me;
    SetSerial::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        //console->setEnabled(true);
        //console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->ConnectAct->setEnabled(false);
        ui->actionIC_set->setEnabled(false);
        ui->ICButton->setEnabled(false);
       // me.exec();
        QMessageBox::information(this,"INFO","Succeed!");
        ui->actionDisconnect->setEnabled(true);
        //ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        //showStatusMessage(tr("Open error"));
    }
}

void MainWindow::IcShow()
{
    IcRead my;
    my.exec();
}

//--------------------------------------------ACTION-------------------------------------------------//
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    ui->ConnectAct->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionIC_set->setEnabled(true);
    ui->ICButton->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}


void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    //console->putData(data);
    qDebug()<<"the data:"<<data;

}


void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}


//-------------------------------------------Configuration------------------------------------------//
void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}


void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

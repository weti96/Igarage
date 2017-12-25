#include "serial_set.h"
#include "ui_serial_set.h"

Serial_Set::Serial_Set(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serial_Set)
{
    ui->setupUi(this);
    m_pStatusLbl = new QLabel(tr("��ӭʹ��QUART���ڹ���!"));
    m_pRxCountLbl = new QLabel("���� : 0");
    m_pRxCountLbl->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_pRxCountLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pTxCountLbl = new QLabel("���� : 0");
    m_pTxCountLbl->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_pTxCountLbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pClearCountBtn = new QPushButton("��λ����");
    ui->statusbar->addWidget(m_pStatusLbl, 3);
    ui->statusbar->addWidget(m_pRxCountLbl, 1);
    ui->statusbar->addWidget(m_pTxCountLbl, 1);
    ui->statusbar->addWidget(m_pClearCountBtn, 1);


#ifdef Q_OS_LINUX
    ui->m_SerNameBox->addItem( "ttyUSB0");
    ui->m_SerNameBox->addItem( "ttyUSB1");
    ui->m_SerNameBox->addItem( "ttyUSB2");
    ui->m_SerNameBox->addItem( "ttyUSB3");
    ui->m_SerNameBox->addItem( "ttyS0");
    ui->m_SerNameBox->addItem( "ttyS1");
    ui->m_SerNameBox->addItem( "ttyS2");
    ui->m_SerNameBox->addItem( "ttyS3");
    ui->m_SerNameBox->addItem( "ttyS4");
    ui->m_SerNameBox->addItem( "ttyS5");
    ui->m_SerNameBox->addItem( "ttyS6");
#elif defined (Q_OS_WIN)
    ui->m_SerNameBox->addItem("COM0");
    ui->m_SerNameBox->addItem("COM1");
    ui->m_SerNameBox->addItem("COM2");
    ui->m_SerNameBox->addItem("COM3");
    ui->m_SerNameBox->addItem("COM4");
    ui->m_SerNameBox->addItem("COM5");
    ui->m_SerNameBox->addItem("COM6");
    ui->m_SerNameBox->addItem("COM7");
    ui->m_SerNameBox->addItem("COM8");
    ui->m_SerNameBox->addItem("COM9");
#endif
    ui->m_SerNameBox->setEditable(true);
    //ui->m_pSendBtn->setEnabled(false);
    //ui->m_pRxTxtEdit->setReadOnly(true);
    m_pUserUart = NULL;

    //m_uiMaxRcvBuff = ui->m_pMaxRcvBuffLEdit->text().toInt();
    connect(m_pClearCountBtn, SIGNAL(clicked()), this ,SLOT(__OnClearCountBtnClicked()));
    connect(ui->m_OpenButton, SIGNAL(clicked()), this ,SLOT(__OnOpenBtnClicked()));
    //connect(ui->m_pSendBtn, SIGNAL(clicked()), this ,SLOT(__OnSendBtnClicked()));
    //connect(ui->m_pRcvClrBtn, SIGNAL(clicked()), this ,SLOT(__OnRcvClrBtnClicked()));
    //connect(ui->m_pMaxRcvBuffLEdit, SIGNAL(textChanged(QString)), this ,SLOT(__OnMaxRcvBuffLEditChanged(QString)));
    //connect(ui->m_pRxTxtEdit, SIGNAL(textChanged()), this ,SLOT(__OnMaxRcvBuffLEditChanged(QString)));

}

Serial_Set::~Serial_Set()
{
    delete ui;
}

void Serial_Set::__UartStateSwitch(bool stats)
{
    QSerialPort *m_pUserUart;
    if(true == stats)
    {
       currentSettings.name = ui->m_SerNameBox->currentText();   //��ȡ������
    #ifdef Q_OS_LINUX
        pMyCom = new QextSerialPort("/dev/" + currentSettings.name);
    #elif defined (Q_OS_WIN)
       // m_pUserUart = new QextSerialPort(uartName);
    #endif
        if (ui->m_BaudBox->currentIndex() == 4) {
            currentSettings.baudRate = ui->m_BaudBox->currentText().toInt();
        } else {
            currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                        ui->m_BaudBox->itemData(ui->m_BaudBox->currentIndex()).toInt());
        }
        currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

        currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                    ui->m_DataBox->itemData(ui->m_DataBox->currentIndex()).toInt());
        currentSettings.stringDataBits = ui->m_DataBox->currentText();

        currentSettings.parity = static_cast<QSerialPort::Parity>(
                    ui->m_CheckBox->itemData(ui->m_CheckBox->currentIndex()).toInt());
        currentSettings.stringParity = ui->m_CheckBox->currentText();

        currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                    ui->m_StopBox->itemData(ui->m_StopBox->currentIndex()).toInt());
        currentSettings.stringStopBits = ui->m_StopBox->currentText();

//        currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
//                    ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
//        currentSettings.stringFlowControl = ui->flowControlBox->currentText();

        currentSettings.localEchoEnabled = ui->m_OpenButton->isChecked();
        //������ʱ
        //m_pUserUart->setTimeout(TIME_OUT);
        //setTimeout(TIME_OUT);


        if(m_pUserUart->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, tr("�򿪳ɹ�"), tr("�ѳɹ��򿪴���") + currentSettings.name, QMessageBox::Ok);
            //�������
            //ui->m_pSendBtn->setEnabled(true);
            ui->m_BaudBox->setEnabled(false);
            ui->m_StopBox->setEnabled(false);
            ui->m_CheckBox->setEnabled(false);
            ui->m_DataBox->setEnabled(false);
            ui->m_SerNameBox->setEnabled(false);

            //ui->m_pTxTxtEdit->setEnabled(true);
            //ui->m_pTxTxtEdit->setFocus();
            //ui->statusBar->showMessage(tr("�򿪴��ڳɹ�"));
            m_pStatusLbl->setText(tr("�򿪴��ڳɹ�"));
        }
        else
        {
            QMessageBox::critical(this, tr("��ʧ��"), tr("δ�ܴ򿪴��� ") + currentSettings.name + tr("\n�ô����豸�����ڻ��ѱ�ռ��"), QMessageBox::Ok);
            //ui->statusBar->showMessage(tr("�򿪴���ʧ��"));
            m_pStatusLbl->setText(tr("�򿪴���ʧ��"));
            m_pUserUart->close();

            //delete m_pUserUart;
           // m_pUserUart = NULL;
            return;
        }


    }
    else
    {
        m_pUserUart->close();
        //delete m_pUserUart;
        //m_pUserUart = NULL;

        //ui->m_pSendBtn->setEnabled(false);
        ui->m_BaudBox->setEnabled(true);
        ui->m_StopBox->setEnabled(true);
        ui->m_CheckBox->setEnabled(true);
        ui->m_DataBox->setEnabled(true);
        ui->m_SerNameBox->setEnabled(true);
        //ui->m_pTxTxtEdit->setEnabled(false);

        //ui->statusBar->showMessage(tr("�����Ѿ��ر�"));
        m_pStatusLbl->setText(tr("�����Ѿ��ر�"));
    }
}

void Serial_Set::set_baud(QSerialPort::BaudRate)
{

}

void Serial_Set::__OnOpenBtnClicked()
{
    if(NULL == m_pUserUart)
    {
        __UartStateSwitch(true);
        if(m_pUserUart != NULL)
        {
            ui->m_OpenButton->setText(tr("�رմ���"));
           // ui->m_pOpenBtn->setIcon(QIcon(":/images/stop.png"));
        }
    }
    else
    {
        __UartStateSwitch(false);
        if(NULL == m_pUserUart)
        {
            ui->m_OpenButton->setText(tr("�򿪴���"));
          //  ui->m_pOpenBtn->setIcon(QIcon(":/images/open.png"));
        }
    }
}

void Serial_Set::__OnReadUserUart()
{

}

void Serial_Set::__OnClearCountBtnClicked()
{
    m_pTxCountLbl->setText(tr("���� : 0"));
    m_pRxCountLbl->setText(tr("���� : 0"));
    m_uiTxByteCounter = 0;
    m_uiRxByteCounter = 0;
    m_pStatusLbl->setText(tr("������պͷ��ͼ����ɹ���"));
}

void Serial_Set::__OnSendBtnClicked()
{

}

void Serial_Set::__OnMaxRcvBuffLEditChanged(QString)
{
   // m_uiMaxRcvBuff = ui->m_pMaxRcvBuffLEdit->text().toInt();
}

void Serial_Set::__OnRxTxtEditTEditChanged()
{

}
//void Serial_Set::setTimeout(long millisec)
//{
//    //Q_D(Serial_Set);
//    QWriteLocker locker(&d->lock);
//    if (d->settings.Timeout_Millisec != millisec)
//        d->setTimeout(millisec, true);
//}

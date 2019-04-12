#include "cdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QMessageBox>

CDialog::CDialog(QWidget *parent) :
    QDialog(parent)
{

    //playOutput = "";

    setWindowTitle(tr("play"));

    //窗口
    setAutoFillBackground(true);

//    QPalette palette = this->palette();
//    palette.setColor(QPalette::Window,Qt::white);
//    setPalette(palette);

    setMinimumSize(150,180);  // 窗口大小
    setMaximumSize(150,180);

    port = new QLabel(tr("端 口："));
    portBox = new QComboBox;
    QStringList list = AvailablePorts();
    portBox->addItems(list);

    baudRate = new QLabel(tr("波特率："));
    baudRateBox = new QComboBox;
    list.clear();
    list <<"1200" <<"2400" <<"4800" <<"9600" <<"19200" <<"38400" <<"57600" <<"115200";
    baudRateBox->addItems(list);
    baudRateBox->setCurrentText("9600");

    openSerial = new QPushButton(tr("打开串口"));
    connect(openSerial, SIGNAL(clicked()), this, SLOT(OnOpenSerialClicked()));
    openSerial->setToolTip(tr("打开串口"));
    openSerial->setToolTipDuration(2000);
    openSerial->setDefault(true);
    openSerial->setEnabled(true);
    openSerial->setStatusTip(tr("打开串口"));
    closeSerial = new QPushButton(tr("关闭串口"));
    connect(closeSerial, SIGNAL(clicked()), this, SLOT(OnCloseSerialClicked()));
    closeSerial->setToolTip(tr("关闭串口"));
    closeSerial->setToolTipDuration(2000);
    closeSerial->setDisabled(true);
    closeSerial->setStatusTip(tr("关闭串口"));

    playSerial = new QPushButton(tr("演示"));
    connect(playSerial, SIGNAL(clicked()), this, SLOT(OnPlaySerialClicked()));


    QHBoxLayout *layout1 = new QHBoxLayout();                 //创建播放速度的水平布局
    layout1->addWidget(port);                             //在布局中添加box和slider
    layout1->addWidget(portBox);

    QHBoxLayout *layout2 = new QHBoxLayout();                 //创建播放速度的水平布局
    layout2->addWidget(baudRate);                             //在布局中添加box和slider
    layout2->addWidget(baudRateBox);

    QVBoxLayout *mLayout = new QVBoxLayout();

//    mainLayout->addStretch();
//    mainLayout->addWidget(label2);
    mLayout->addLayout(layout1);
    mLayout->addLayout(layout2);
    mLayout->addStretch();
    mLayout->addWidget(openSerial);
    mLayout->addWidget(playSerial);
    mLayout->addWidget(closeSerial);

    setLayout(mLayout);


}

CDialog::~CDialog()
{
   // delete(this);
}


QStringList CDialog::AvailablePorts()
{
    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        //qDebug() << "Name        : " << info.portName();
        list << info.portName();
    }
    if (list.empty() == true)
    {
        list << "Com1";
    }
    return list;
}

void CDialog::OnOpenSerialClicked()
{
    mySerialPort = new QSerialPort();
    mySerialPort->setPortName(portBox->currentText());
    if(mySerialPort->open(QIODevice::ReadWrite))                  //设置为打开的状态
    {
        mySetBaudRate(baudRateBox->currentIndex());          //波特率
//        mySerialPort->setBaudRate(QSerialPort::Baud9600);  // 波特率
        mySerialPort->setDataBits(QSerialPort::Data8);       // 数据位
        mySerialPort->setParity(QSerialPort::NoParity);      // 校验位
        mySerialPort->setStopBits(QSerialPort::OneStop);     // 停止位
        mySerialPort->setFlowControl(QSerialPort::NoFlowControl);

//    connect(mySerialPort, SIGNAL(readyRead()), this, SLOT(OnSerialRcvUpdate()));

    portBox->setDisabled(true);
    baudRateBox->setDisabled(true);
//    dataBitsBox->setDisabled(true);
//    parityBox->setDisabled(true);
//    stopBitsBox->setDisabled(true);
    closeSerial->setEnabled(true);
    openSerial->setDisabled(true);
    }
    else
    {
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Retry);
    }
}

void CDialog::OnCloseSerialClicked()
{
    if (mySerialPort->isOpen())
    {
        mySerialPort->close(); // 关闭并移除串口
        delete mySerialPort;

        portBox->setEnabled(true);
        baudRateBox->setEnabled(true);

        closeSerial->setDisabled(true);
        openSerial->setEnabled(true);
    }

}

void CDialog::OnPlaySerialClicked()
{
//    QString temPlayOutput = "1234567";
//    QString sendstr(temPlayOutput);
//    QByteArray sdata;
//    sdata.append(sendstr);
//    mySerialPort->write(sdata,sdata.length());

    QString sendstr(playOutput);
    QByteArray sdata;
    sdata.append(sendstr);
    mySerialPort->write(sdata,sdata.length());

}

void CDialog::mySetBaudRate(int baudRate)
{
    if(baudRate==1200)
        mySerialPort->setBaudRate(QSerialPort::Baud1200);
    else if(baudRate==2400)
        mySerialPort->setBaudRate(QSerialPort::Baud2400);
    else if(baudRate==4800)
        mySerialPort->setBaudRate(QSerialPort::Baud4800);
    else if(baudRate==9600)
        mySerialPort->setBaudRate(QSerialPort::Baud9600);
    else if(baudRate==19200)
        mySerialPort->setBaudRate(QSerialPort::Baud19200);
    else if(baudRate==38400)
        mySerialPort->setBaudRate(QSerialPort::Baud38400);
    else if(baudRate==115200)
        mySerialPort->setBaudRate(QSerialPort::Baud115200);
}

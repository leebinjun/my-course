#ifndef MYDIALOG_H
#define MYDIALOG_H

#include "keyevent.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
#include <QSerialPort>

class CDialog : public QDialog
{
    Q_OBJECT

public:
//    CDialog();
    ~CDialog();

public:
    explicit CDialog(QWidget *parent = 0);

    QStringList AvailablePorts();

    QString playOutput;

signals:

public slots:
    void OnOpenSerialClicked();
    void OnCloseSerialClicked();
    void OnPlaySerialClicked();


private:

    QSerialPort *mySerialPort;

    QLabel *port;               // 端口
    QComboBox *portBox;
    QLabel *baudRate;           // 波特率
    QComboBox *baudRateBox;

    QPushButton *openSerial;    // 打开串口
    QPushButton *playSerial;    // 演示
    QPushButton *closeSerial;   // 关闭串口

public:
    void mySetBaudRate(int baudRate);



};

#endif // MYDIALOG_H

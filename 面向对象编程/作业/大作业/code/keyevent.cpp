#include "workthread.h"
#include "keyevent.h"
#include "horse.h"
#include "cDialog.h"
#include <QPainter>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QWidget>
#include <QLineEdit>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMutex>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>


QPushButton *startBtn;  //开始按键
QPushButton *stopBtn;   //终止按键
QPushButton *pauseBtn;  //暂停、继续按键
QPushButton *printBtn;  //打印按键
QPushButton *quitBtn;   //退出按键

QPushButton *playBtn;   //发挥按键

QPushButton *loadBtn;   //载入按键
QPushButton *saveBtn;   //保存按键

QLabel *label1;         //标签1：播放速度
QSpinBox *spinBox1;     //帧数设置盒子
QSlider *slider1;       //帧数设置滑块

QLabel *label2;         //标签2：起始位置
QLabel *label2_1;       //标签2_1：X起始位置
QLabel *label2_2;       //标签2_2：Y起始位置
QSpinBox *spinBox2_1;   //起始位置X SpinBox
QSpinBox *spinBox2_2;   //起始位置Y SpinBox

QTextEdit *textEdit;    //多行文本

#define  SAVE_DATA    "result/J_SAVE.dat"

bool flag_startBtn = 0;
bool flag_pauseBtn = 0;
bool flag_loadBtn = 0;
bool flag_pop = 1;
bool flag_loadBtn_start = 0;

int loadstep = 0; // 定义载入结果的步数

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
{

    workhorse = new Horse();//WorkThread();
    workhorse->record[0][0]=0;
    workhorse->record[0][1]=1; //遇上这种问题，往往是你使用了没初始化的指针，或者已释放的指针。

//    setWindowTitle(tr("binjun的跳马场"));
    setWindowTitle(tr("骑士周游问题"));
    setWindowIcon(QIcon("test.ico")); // 图标


    //窗口
    setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,Qt::white);
    setPalette(palette);

    setMinimumSize(570,400);  // 窗口大小
    setMaximumSize(570,400);

    //棋盘
    //width=size().width();
    width=20+45*8+1;
    //height=size().height();
    height=20+45*8+1;

    pix = new QPixmap(width,height);
    pix->fill(Qt::white);

    image.load(":/images/002.png");  // 马儿图标
    startX=0;   // 马初始位置
    startY=0;
    m_step=45;  // 棋盘格大小，由马图标决定了


    // 按键布局
    startBtn = new QPushButton(tr("开始"));
    stopBtn  = new QPushButton(tr("停止"));
    quitBtn  = new QPushButton(tr("退出"));
    pauseBtn = new QPushButton(tr("暂停"));
    printBtn = new QPushButton(tr("打印"));
    loadBtn = new QPushButton(tr("载入"));
    saveBtn = new QPushButton(tr("保存"));
    playBtn = new QPushButton(tr("play"));
    startBtn->setDefault(true); //该函数将按钮button设置为默认按钮，即用户按回车键事即点击按钮。
    stopBtn->setEnabled(false);
    pauseBtn->setEnabled(false);
    printBtn->setEnabled(false);
    saveBtn->setEnabled(false);



    label2 = new QLabel("起始位置");
//    label2_1 = new QLabel("strtX");
    label2_1 = new QLabel("列数");
//    label2_2 = new QLabel("strtY");
    label2_2 = new QLabel("行数");
    spinBox2_1 = new QSpinBox;                  //创建SpinBox
    spinBox2_1->setRange(1, 8);                 //设置spinBox的值范围
    spinBox2_1->setValue(1);                    //设定spinBox的初始值
    spinBox2_2 = new QSpinBox;                  //创建SpinBox
    spinBox2_2->setRange(1, 8);                 //设置spinBox的值范围
    spinBox2_2->setValue(1);                    //设定spinBox的初始值

    label1 = new QLabel("播放速度");
    spinBox1 = new QSpinBox;                    //创建SpinBox
    slider1 = new QSlider(Qt::Horizontal);      //创建一个水平方向的 QSlider
    spinBox1->setRange(1, 500);               //设置spinBox的值范围
    slider1->setRange(1, 500);                //设置slider的值范围
    spinBox1->setValue(100);                    //设定spinBox的初始值
    slider1->setValue(100);                     //设定slider的初始值

    textEdit = new QTextEdit();
    textEdit->setMinimumSize(157,100);          //设置文本框大小
    textEdit->setMaximumSize(157,100);
//    textEdit->setText("我是第一行<br/>我是第二行");
    textEdit->show();

//    button->setFont(QFont("times",16,QFont::Bold));//设置按钮标签的字体，字号和样式。
//    QPixmap pixmap（"somepixmap.xpm"）;
//    button->setPixmap(pixmap);//这两句在一起可以为按钮添加一个位图标签，somepixmap.xpm是你选择的位图。
//    startBtn->setDefault(true); //该函数将按钮button设置为默认按钮，即用户按回车键事即点击按钮。

//    //弹簧，可以控制组件的显示位置
//    buttonLayout->addStretch(1);
//    buttonLayout->addWidget(startBtn,1);
//    buttonLayout->addWidget(stopBtn,1);
//    buttonLayout->addWidget(quitBtn,1);
//    buttonLayout->addStretch(1);
//    //通过下面的方法可以设置每个button的间隔距离
//    buttonLayout->setSpacing(50);

//    QVBoxLayout *buttonLayout = new QVBoxLayout(this);  //使用垂直布局类QVBoxLayout

//    QGridLayout *gridLayout = new QGridLayout;
//    gridLayout->setColumnStretch(0, 1);
//    gridLayout->setColumnStretch(1, 4);
//    gridLayout->setColumnStretch(2, 1);

//    gridLayout->addWidget(startBtn, 0, 0);
//    gridLayout->addWidget(stopBtn, 0, 1);
//    gridLayout->addWidget(quitBtn, 0, 2);


//    HeadLabel =new QLabel(tr("头像： "));          //右上角部分
//    UpdateHeadBtn =new QPushButton(tr("更新"));

//    TopRightLayout =new QHBoxLayout();
//    TopRightLayout->setSpacing(20);
//    TopRightLayout->addWidget(HeadLabel);
//    TopRightLayout->addWidget(UpdateHeadBtn);

    // 按键布局,参考http://blog.csdn.net/liang19890820/article/details/51537246

    QHBoxLayout *layout5 = new QHBoxLayout();                 //创建停止打印按键的水平布局
    layout5->addWidget(stopBtn);
    layout5->addWidget(printBtn);

    QHBoxLayout *layout4 = new QHBoxLayout();                 //创建载入保存按键的水平布局
    layout4->addWidget(loadBtn);
    layout4->addWidget(saveBtn);

    QHBoxLayout *layout3 = new QHBoxLayout();                 //创建开始暂停继续按键的水平布局
    layout3->addWidget(startBtn);
    layout3->addWidget(pauseBtn);

    QHBoxLayout *layout2 = new QHBoxLayout();                 //创建起始位置的水平布局
    layout2->addWidget(label2_1);                             //在布局中添加X
    layout2->addWidget(spinBox2_1);                           //在布局中添加X的slider
    layout2->addWidget(label2_2);                             //在布局中添加Y
    layout2->addWidget(spinBox2_2);                           //在布局中添加Y的slider


    QHBoxLayout *layout1 = new QHBoxLayout();                 //创建播放速度的水平布局
    layout1->addWidget(spinBox1);                             //在布局中添加box和slider
    layout1->addWidget(slider1);

    QVBoxLayout *mainLayout = new QVBoxLayout();

//    mainLayout->addStretch();
    mainLayout->addWidget(label2);
    mainLayout->addLayout(layout2);
    mainLayout->addStretch();
//    mainLayout->addWidget(spinBox, 0, Qt::AlignLeft);
//    mainLayout->addWidget(slider, 0, Qt::AlignRight);
    mainLayout->addWidget(label1);
    mainLayout->addLayout(layout1);
    mainLayout->addStretch();
    mainLayout->addWidget(textEdit);
    mainLayout->addStretch();
//    mainLayout->addWidget(loadBtn);
//    mainLayout->addWidget(saveBtn);
    mainLayout->addLayout(layout4);
    mainLayout->addLayout(layout3);
//    mainLayout->addWidget(startBtn);
//    mainLayout->addWidget(pauseBtn);
    mainLayout->addLayout(layout5);
//    mainLayout->addWidget(stopBtn);
//    mainLayout->addWidget(printBtn);
    mainLayout->addWidget(playBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(quitBtn);
//    mainLayout->addWidget(startBtn, 0, Qt::AlignRight);
//    mainLayout->addWidget(stopBtn, 0, Qt::AlignRight);
//    mainLayout->addWidget(quitBtn, 0, Qt::AlignRight);


    QHBoxLayout *biggestLayout = new QHBoxLayout(this);    //设置总网络布局
    biggestLayout->addStretch();
    biggestLayout->addStretch();
    biggestLayout->addStretch();
    biggestLayout->addLayout(mainLayout);
//    QGridLayout *mainLayout = new QGridLayout(this);     //设置网格布局
//    mainLayout->setColumnStretch(0, 1);
//    mainLayout->setRowStretch(2, 1);


//    mainLayout->addWidget(label1, 1, 2);
//    mainLayout->addWidget(spinBox, 2, 2);
//    mainLayout->addWidget(slider, 2, 3);

//    mainLayout->addWidget(startBtn, 5, 2);
//    mainLayout->addWidget(stopBtn, 6, 2);
//    mainLayout->addWidget(quitBtn, 7, 2);


    this->connect(startBtn,SIGNAL(clicked()),this,SLOT(slotStart()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(slotStop()));
    connect(pauseBtn,SIGNAL(clicked()),this,SLOT(slotPause()));
    connect(printBtn,SIGNAL(clicked()),this,SLOT(slotPrint()));
    connect(quitBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveData()));
    connect(loadBtn,SIGNAL(clicked()),this,SLOT(loadData()));
    connect(playBtn,SIGNAL(clicked()),this,SLOT(slotPlay()));

    connect(spinBox1, SIGNAL(valueChanged(int)),
                    slider1, SLOT(setValue(int)));           //spinBox1的值发生变化时，slider1值也跟着变化
    connect(slider1, SIGNAL(valueChanged(int)),
                    spinBox1, SLOT(setValue(int)));          //slider1的值发生变化时，spinBox1值也跟着变化
    // 滑动slider，弹出一个彩蛋窗口
    connect(slider1, SIGNAL(sliderPressed()),
                    this, SLOT(pop()));

    connect(spinBox2_1, SIGNAL(valueChanged(int)), this, SLOT(starValueChange()));
    connect(spinBox2_2, SIGNAL(valueChanged(int)), this, SLOT(starValueChange()));

//    startBtn->setGeometry(QRect(400, 40, 150, 30));//设置按钮的位置和大小，前两个表示按钮距离父窗口左上角的坐标像素的位置，后两个表示按钮的大小。
//    stopBtn->setGeometry(QRect(400, 80, 150, 30));
//    quitBtn->setGeometry(QRect(400, 120, 150, 30));

    drawPix();
    resize(450,600);
}

KeyEvent::~KeyEvent()
{

}

void KeyEvent::drawPix()
{
//    int last_startX;
//    int last_startY;

    pix->fill(Qt::white);
    QPainter *painter = new QPainter;
    QPen pen(Qt::black, 1.5, Qt::DashDotLine, Qt::RoundCap);
    for(int i=20;i<width;i=i+m_step)
    {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(i,20),QPoint(i,height));
        painter->end();
    }
    for(int j=20;j<height;j=j+m_step)
    {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(20,j),QPoint(width,j));
        painter->end();
    }
    painter->begin(pix);
    painter->drawImage(QPoint(startX+28,startY+23),image); // 画小马图标
//    painter->drawText(QPoint(startX+28,startY+23),"hello"); // srawText测试
//    painter->drawText(0,0,"helloworld");
    painter->end();


    if(flag_startBtn || flag_loadBtn) // 如果开始按键被按下，即进去算法执行中，再画一个数字记录路径
//    {
//        painter->begin(pix);
//        painter->drawText(QPoint(last_startX+28,last_startY+23), QString(workhorse->h_step));
//        painter->end();
//    }
    {
        flag_loadBtn = 0;
//        startX = workhorse->record[step][1];
//        startY = workhorse->record[step][0];
//      int step = workhorse->h_step; // 获取当前马儿走的步数
//       for(int i = 0; i < step; i++)
//       {
//           painter->begin(pix);
//           painter->drawText(QPoint(workhorse->record[i][1]*45+28,workhorse->record[i][0]*45+23), QString(i));
//           painter->end();
//       }

        //显示数字
        for(int i=0;i<MAXN;i++)
        {
            for(int j=0;j<MAXN;j++)
            {
                if(workhorse->map[i][j]<= workhorse->h_step && workhorse->map[i][j]!=0)
                {
                    painter->begin(pix);
                    painter->drawText(QPoint(j*45+30,i*45+30), QString::number(workhorse->map[i][j]));
                    //qDebug()<<workhorse->map[i][j];
                    //qDebug("%3d%3d",record[i][0],record[i][1]);
                    painter->end();

                }
            }
        }


//        qDebug()<<workhorse->h_step;
//        qDebug()<<"hellooo";

        //显示折线
        for(int i = 1; i <= workhorse->h_step; i++)
        {
            painter->begin(pix);
            painter->setPen(Qt::red);//设置钢笔颜色
            painter->drawLine(QPoint(workhorse->record[i-1][1]*45+43,workhorse->record[i-1][0]*45+43),
                              QPoint(workhorse->record[i][1]*45+43,workhorse->record[i][0]*45+43));
            //qDebug()<<workhorse->map[i][j];
            painter->end();

        }

        //文本框打印
        if(flag_startBtn == 1 && flag_pauseBtn == 0)
        {
            int temp = workhorse->h_step;
            textEdit->setText("当前步数:"+QString::number(temp-1)+"\n"
                             +"当前位置:"+QString::number(workhorse->record[temp][0]+1)+"行,"
                                        +QString::number(workhorse->record[temp][1]+1)+"列");
        }


    }
//    last_startX = startX;
//    last_startY = startY;

//    int sx = startX;
//    int sy = startY;
//    QLabel *lbl = new QLabel(this);
//    QFont lbl_font;
//    lbl_font.setPointSize(16);                          // 设置字体大小
//    lbl->setFont(lbl_font);
//    lbl->setText("Hello World.");
//    lbl->setGeometry(QRect(400, 20, 150, 30));          // 设置大小和位置
//    lbl->setFrameStyle(QFrame::Panel | QFrame::Sunken); // 设置外观
//    lbl->setText(QString::number(sx)+","+QString::number(sy)+"+test99");

}

//通过box改变马儿的初始位置
void KeyEvent::starValueChange()
{
    startX = 45*(spinBox2_1->value()-1); //设置起始位置
    startY = 45*(spinBox2_2->value()-1);
    qDebug("startX:%d,starty:%d",startX/45,startY/45);
    drawPix();
    update();
}

//这其实是一个彩蛋
void KeyEvent::pop()
{
    if (flag_pop == 1)
    {
        flag_pop = 0;
        QMessageBox::information(NULL, "Surprice!", "Now you can use kye“WASD” to change horse initial positon"
                                 , QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

//通过WASD四个按键可以改变马儿的初始位置
void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    startX=startX-startX%m_step;
    startY=startY-startY%m_step;
    if(event->key()==Qt::Key_A)
    {
        startX=(startX-m_step<0)?startX:startX-m_step;
    }
    if(event->key()==Qt::Key_D)
    {
        startX=(startX+m_step+image.width()>width)?startX:startX+m_step;
    }
    if(event->key()==Qt::Key_W)
    {
        startY=(startY-m_step<0)?startY:startY-m_step;
    }
    if(event->key()==Qt::Key_S)
    {
        startY=(startY+m_step+image.height()>height)?startY:startY+m_step;
    }
    if(event->key()==Qt::Key_Home)
    {
        startX=0;
        startY=0;
    }
    if(event->key()==Qt::Key_End)
    {
        startX=width-image.width();
        startY=height-image.height();
    }

    qDebug("startX:%d,starty:%d",startX/45,startY/45);
    drawPix();
    update();
}

void KeyEvent::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0,0),*pix);
    painter.end();
    if(flag_startBtn) // 如果开始按键被按下，即进去算法执行中，调用horserunEvent()更新画板
        horserunEvent();
    if(flag_loadBtn)  // 如果载入按键被按下，即显示中间结果时，调用horserunEvent()更新画板
    {
        qDebug() << "aaaaaaaaa";
        horserunEvent();
    }
}

void KeyEvent::horserunEvent()
{
    int step = workhorse->h_step; // 获取当前马儿位置，记住乘以棋盘格大小m_step，
    startX = workhorse->record[step][1];
    startY = workhorse->record[step][0];
    startX *= 45;
    startY *= 45;
    //qDebug("startX:%d,starty:%d",startX,startY);
    drawPix();
    update();
}



//"开始"按键响应函数
void KeyEvent::slotStart()
{

    flag_startBtn = 1;
    flag_pauseBtn = 0; //每次重新开始后，务必清零flag_pauseBtn
//    Horse *workhorse = new Horse();//WorkThread();



    if(flag_loadBtn_start == 0) //判断是重新开始还是载入中间结果后继续运行
    {
        workhorse = new Horse();//WorkThread();
        workhorse->setStartValue(startY/45, startX/45);  //设置起始位置
//        qDebug("\n");
        memset(workhorse->map,0,sizeof(workhorse->map));//将8*8的棋盘全部置为0
        workhorse->h_step=1;
        workhorse->record[0][0] = workhorse->iX;
        workhorse->record[0][1] = workhorse->iY;
    }
    else
    {
        //map
        //memset(map,0,sizeof(map));//将8*8的棋盘全部置为0
        //qDebug() << workhorse->h_step++;
        int temp = workhorse->h_step;
        workhorse->setStartValue(workhorse->record[temp][0],
                                 workhorse->record[temp][1]);  //设置起始位置
    }
    workhorse->m_runFrame =  spinBox1->value();       //设置刷新频率
    workhorse->start();

    startBtn->setEnabled(false);   // 防止用户乱按键，玩崩
    stopBtn->setEnabled(true);
    pauseBtn->setEnabled(true);
    printBtn->setEnabled(false);
    loadBtn->setEnabled(false);
    saveBtn->setEnabled(false);


}

//"停止"按键响应函数
void KeyEvent::slotStop()
{
    flag_startBtn = 0;
    flag_loadBtn_start = 0;

    workhorse->terminate(); // 强制终止线程，小概率Crash
//    workhorse->exit();
//    workhorse->quit();
    workhorse->wait();
    //下面这行取消注释的话printSlop()容易崩溃
//    workhorse->deleteLater();


    //workhorse->pause.lock();

//    for(int i=0;i<MAXSIZE;i++)
//    {
//        workThread[i]->terminate();
//        workThread[i]->wait();
//    }
    pauseBtn->setText("暂停");    // 防止用户乱按键，玩崩
    pauseBtn->setEnabled(false);
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
    printBtn->setEnabled(true);
    loadBtn->setEnabled(true);
    saveBtn->setEnabled(true);
}

//"暂停继续"按键响应函数
void KeyEvent::slotPause()
{
    if (flag_startBtn == 1) // 设置按键使能，加flag防止用户乱按键，玩崩
    {
        if (flag_pauseBtn == 0)
        {
            pauseBtn->setText("继续");
            printBtn->setEnabled(true);
            saveBtn->setEnabled(true);
            workhorse->pause.lock();
        } else {
            pauseBtn->setText("暂停");
            printBtn->setEnabled(false);
            saveBtn->setEnabled(false);
            workhorse->pause.unlock();
        }
    }
    flag_pauseBtn = 1 - flag_pauseBtn;

}

//"打印"按键响应函数
void KeyEvent::slotPrint()
{

    qDebug("%3d", workhorse->h_step);
    for(int i=0;i<= workhorse->h_step;i++){
        qDebug("%3d%3d%3d", i, workhorse->record[i][0], workhorse->record[i][1]);
    }

    //文本框打印
    int temp = workhorse->h_step;
    QString output = "";
    output = "步数：" + QString::number(temp-1) + "\n";
    for(int i=1;i<= workhorse->h_step;i++)
    {
        output += (QString::number(workhorse->record[i][0]+1)+"行,"
                         +QString::number(workhorse->record[i][1]+1)+"列\n");
    }
    textEdit->setText(output);

}

//文件读写函数
//保存程序运行的结果
void KeyEvent::saveData()
{
    //test
//    QString filename = "J:\qt\build-005-Desktop_Qt_5_3_MinGW_32bit-Debug\debug\test.txt";        //当前文件夹中
//    QString str = "Qt QFile Test...";  //保存的文本内容
//    QFile file(filename);
//    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
//    {
//        QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
//    }
//    QTextStream in(&file);
//    in<<str<<"\n";
    QString filename = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());//获取需要保存成的文件名
    if(filename.isEmpty())
    {
        QMessageBox::information(this,"ErrorBox","Please input the filename");
        return;
    }
    else
    {
        QFile *file = new QFile;
        file->setFileName(filename);
        bool ok = file->open(QIODevice::Text | QIODevice::WriteOnly);

        if(ok)
        {
//            QTextStream out(file);
//            out<<ui->textEdit->toPlainText(); //转化成纯文本
//            file->close();
//            delete(file);

            //文本输出流，用于保存数据
            QTextStream Out(file);
            //加入空格的好处是以流的形式读取恰好是相反的操作，这样一来方便快速对参数的读取
            for(int i=1; i<= workhorse->h_step+1; i++)
            {
                Out << i-1;
                Out << ' ';
                Out << workhorse->record[i-1][0]+1;
                Out << ' ';
                Out << workhorse->record[i-1][1]+1;
                Out << endl;                      //使用QTextStream向txt文件输出换行时，需要使用QIODevice::Text标志
            }
            file->close();
            delete(file);
        }
        else
        {
            QMessageBox::information(this,"ErrorBox","file fail to save");
        }
    }




}

//加载程序运行保存的结果
QString h_data;
void KeyEvent::loadData()
{
    int i;

    saveBtn->setEnabled(false); //载入之后没有必要按保存

    workhorse = new Horse();//WorkThread();
    memset(workhorse->map,0,sizeof(workhorse->map));//将8*8的棋盘全部置为0


    //获取文件名称
        QString fileName = QFileDialog::getOpenFileName(this,"OpenFile",QDir::currentPath());
        if(fileName.isEmpty())
        {
             QMessageBox::information(this,"Error","Please select a txt");
             return;
        }
        else
        {
             QFile *file = new QFile;
             file->setFileName(fileName);//新建一个文件对象，并且把它设置为上面获取的文件
             bool ok=file->open(QIODevice::ReadOnly | QIODevice::Text);//设置打开模式

             if(ok)//如果可以打开
             {
             //    h_data = QString(file->readAll());  // 读取result并在文本框中显示
             //    textEdit->setText(h_data);

                 QTextStream txtInput(file); //将文件与文本流相关联
             //    QString lineStr;
             //    while(!txtInput.atEnd())
             //    {
             //        lineStr = txtInput.readLine();
             //        cout << lineStr << endl;
             //    }

                 while(!txtInput.atEnd())
                 {
                     QString temps;
                     temps = QString(file->readLine()).trimmed();
                     QStringList templist = temps.split(" ");
                     qDebug() << templist[0] << templist[1] << templist[2];
                     i = templist[0].toInt()+1;
                     qDebug() << i << "step";
                     int temp1 = templist[1].toInt();
                     workhorse->record[i-1][0] = temp1-1;
             //        qDebug() << templist[1].toInt();
             //        qDebug() << temp1;
             //        qDebug() << workhorse->record[i-1][0];

                     int temp2 = templist[2].toInt();
                     workhorse->record[i-1][1] = temp2-1;
             //        qDebug() << templist[2].toInt();
             //        qDebug() << temp2;
             //        qDebug() << workhorse->record[i-1][1];

                     // workhorse.map
                     workhorse->map[temp1-1][temp2-1] = i-1;

                 }

                 loadstep = i;
                 workhorse->h_step = i;             // 文本框显示载入的结果
                 int temp = workhorse->h_step;
                 QString output = "";
                 output = "步数：" + QString::number(temp-1) + "\n";
                 for(int i=0; i<temp; i++)
                 {

                     output += (QString::number(workhorse->record[i][0]+1)+"行,"
                                      +QString::number(workhorse->record[i][1]+1)+"列\n");

                     workhorse->h_step = i;
                     flag_loadBtn = 1;                   // 载入标志置1
                     QPainter *painter = new QPainter;   // 显示当前载入的中间的结果
                 }
                 textEdit->setText(output);
                 //qDebug() << "qqqqqqqqqqqq";

                 file->close();//关闭文件
                 delete(file);//释放文件进程
                 flag_loadBtn_start = 1;  // 载入按键开始标志置1
              }
              else
              {
                  QMessageBox::information(this,"Error Box","FileOpen Error"+file->errorString());
              }
        }

}


CDialog *dialog;
//"play"按键响应函数
void KeyEvent::slotPlay()
{
    dialog = new CDialog();
    //新建一个窗口对象，其中的this指定了新的窗口的父对象是MainWindow，在销毁Mainwindow时也会销毁子对象，即该窗口对象
//    dialog = new myDialog(this);
    //Modal属性决定了show()应该将弹出的dialog设置为模态还是非模态
    //默认情况下该属性为false并且show（）弹出的窗口是非模态的
    //把这个属性设置为true就详单与设置QWidget::windowModality为Qt::ApplicationModal
    //执行exec（）忽略这个Modal这个属性，并且把弹出的dialog设置为模态的



//    dialog->setModal(false);    //此处ture为模态，false为非模态
//    dialog->setModal(true);    //此处ture为模态，false为非模态

//    文本框打印
    int temp = workhorse->h_step;
    qDebug() << temp;
    //dialog->playOutput = "";
    for(int i=1; i<= temp; i++)
    {
        dialog->playOutput += (QString::number(workhorse->record[i][0]+1)+" "
                         +QString::number(workhorse->record[i][1]+1)+"\n");
    }
//    qDebug() << "hello" ;

    dialog->exec();
//    dialog->show();
}


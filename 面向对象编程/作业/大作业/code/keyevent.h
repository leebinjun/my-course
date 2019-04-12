#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "workthread.h"
#include "horse.h"
#include "cdialog.h"

#define MAXSIZE 5

//// 定义按键的标志位
//bool flag_startBtn = 0;
//bool flag_pauseBtn = 0;
//bool flag_loadBtn = 0;
//bool flag_pop = 1;
//bool flag_loadBtn_start = 0;

//int loadstep = 0; // 定义载入结果的步数

class KeyEvent : public QWidget
{
    Q_OBJECT

public:
    KeyEvent(QWidget *parent = 0);
    ~KeyEvent();
    void drawPix();                         // 图形绘制
    void keyPressEvent(QKeyEvent *);        // WASD按键响应，修改马起始坐标
    void paintEvent(QPaintEvent *);         // 绘制事件
private:
    QPixmap *pix;
    QImage image;    // 马的图标

    int width;
    int height;
    int m_step;     // 马走过的步数
public:
    volatile int startX;
    volatile int startY;
    void horserunEvent();  // 马坐标更新

public slots:
    void slotStart();      // 各个按键对应的槽
    void slotStop();
    void slotPause();
    void slotPrint();
    void starValueChange();

    void loadData();
    void saveData();

    void slotPlay();
    void pop();           // 滑动slider时弹出彩蛋

public:
    //WorkThread *workhorse;
    //WorkThread *workThread[MAXSIZE];

    Horse *workhorse;//WorkThread();
    //CDialog *dialog;


};

#endif // KEYEVENT_H

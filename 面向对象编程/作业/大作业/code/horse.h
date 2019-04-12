#ifndef HORSE_H
#define HORSE_H

#include <QDebug>
#include <QString>
#include <QThread>
#include <QPainter>
#include <QMutex>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>

#define MAXN 8
const int MaxQueueSize=64;

class Horse : public QThread,public QPainter
{    Q_OBJECT

public:
    Horse();
    int iX; // 起始点
    int iY;
    void setStartValue(int , int ); // 设置起始点

protected:
    void run();

public:
    struct point {
        int x;//马的x方向
        int y;//马的y方向
    };

private:
    typedef struct Queue{
        struct point  queue[MaxQueueSize];
        int front;//头指针
        int rear;//尾指针
        int tag;//设置标记位
    }SeqCQueue;

    SeqCQueue Q;

    //初始化队列操作
    void QueueInitiate(SeqCQueue *Q);

    //判断队列是否为空
    int QueueNotEmpty(SeqCQueue Q);

    //入队操作
    void  QueueAppend(SeqCQueue *Q,point  x);

    //出队操作
    void QueuePop(SeqCQueue *Q,point  *d);


public:
    //int m_startX,m_startY;//起始位置
    volatile int h_step;//记录马走的步数
    int map[MAXN][MAXN];//8*8的国际象棋棋盘
    volatile int record[64][2];//记录每步的位置
    const int dir[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};//马理论上所能走全部的位置

private:
    //求出该位置的马所能走的步数
    int _step(int x,int y);
    int BFS(point s);

public:
    int work();
    int m_runFrame;
    QMutex pause;

};

#endif // HORSE_H

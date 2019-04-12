#include "workthread.h"
#include <QtDebug>

WorkThread::WorkThread()
{
}

void WorkThread::setStartValue(int startX, int startY)
{
    this->istartX = startX;
    this->istartY = startY;
}

void WorkThread::run()
{
    qDebug()<<this->istartX<<this->istartY;
//    while(true)
//    {
//        for(int n=0;n<10;n++)
//            qDebug()<<n<<n<<n<<n<<n<<n<<n<<n;
//    }





}


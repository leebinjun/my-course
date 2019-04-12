#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
    void setStartValue(int , int );

protected:
    void run();

private:
    int istartX;
    int istartY;
};

#endif // WORKTHREAD_H

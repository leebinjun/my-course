#include "horse.h"
#include "keyevent.h"
#include <QPainter>

extern bool flag_loadBtn_start;
extern int loadstep;

//初始化函数
void Horse::setStartValue(int a1, int a2) // 设置起始点
{
    this->iX = a1;
    this->iY = a2;
}

//队列函数
//初始化队列操作
void Horse::QueueInitiate(SeqCQueue *Q){
    Q->front=0;
    Q->rear=0;
    Q->tag=0;
}

//判断队列是否为空
int Horse::QueueNotEmpty(SeqCQueue Q){
    if(Q.front==Q.rear&&Q.tag==0)
        return 0;
    else
        return 1;
}

//入队操作
void Horse::QueueAppend(SeqCQueue *Q,point  x){
    if(Q->tag==1&&Q->front==Q->rear){
        printf("队列已满，无法插入！\n");
    }else {
        Q->queue[Q->rear]=x;
        Q->rear=(Q->rear+1)%MaxQueueSize;
        Q->tag=1;
    }
}

//出队操作
void Horse::QueuePop(SeqCQueue *Q,point  *d){
    if(Q->tag==0&&Q->front==Q->rear){
        printf("队列已空，无元素可以出队列！\n");
    }else {
        *d=Q->queue[Q->front];
        Q->front=(Q->front+1)%MaxQueueSize;
        Q->tag=0;
    }
}


//算法函数
//采用深度搜索，用回溯的话会慢死
int Horse::_step(int x,int y){
    int i,xi,yi;
    int count=0;
    for( i=0;i<8;i++){
        xi=x+dir[i][0];
        yi=y+dir[i][1];
        //边界条件以及!map[xi][yi]表示未走过的位置
        if(xi>=0&&xi<=MAXN-1&&yi>=0&&yi<=MAXN-1&&!map[xi][yi])
            count++;
    }
    return count;
}

int Horse::BFS(point s)
{
    int i,x,y;
    QueueInitiate(&Q);//初始化队列
    QueueAppend(&Q,s);//入队操作
    point hd ;

    //当队列非空时，进行广度优先搜索
    while(QueueNotEmpty(Q))
    {
        QueuePop(&Q,&hd);//出队列

        record[h_step][0] = hd.x;
        record[h_step][1] = hd.y;
        map[hd.x][hd.y] = h_step;//标记该位置已走过

//12.8//放弃在算法运行中执行绘制
//        QPainter *painter = new QPainter;
//        msleep(m_runFrame);// 修改此处设置刷新频率

        h_step++;//标记该位置已走过
//        printf("%d,%d\n",hd.x,hd.y);//输出走过的位置
//        qDebug("%d,%d\n",hd.x,hd.y);//输出走过的位置

        //记录走过的位置
        int minstep=10;//初始的最小步数
        int flag=0;//标记
        //8个方向进行搜索
        for( i=0;i<8;i++){
            x=hd.x+dir[i][0];
            y=hd.y+dir[i][1];
            if(x>=0&&x<=MAXN-1&&y>=0&&y<=MAXN-1&&!map[x][y]){
                //如果小于当前的最小步数，则让队列元素出队列，并让当前的元素入队列
                if(_step(x,y)<minstep){
                    minstep=_step(x,y) ;
                    point t ,th ;
                    t.x=x,t.y=y ;
                    if(flag) QueuePop(&Q,&th) ;//如果是第一次的话，就不用出队列了；
                    QueueAppend(&Q,t) ;
                    flag=1;
                }
            }
        }
    }
    return h_step-1;
}

int Horse::work()
{

}

void Horse::run()
{

    int m = this->iX;
    int n = this->iY;
//    //判断起始位置是否合法
//    if(m<0||m>7||n<0||n>7){
//        qDebug("起始位置不合法！\n\n");
//    }else {
//        qDebug("\n");
//        memset(map,0,sizeof(map));//将8*8的棋盘全部置为0
    point start;
    start.x=m,start.y=n;
//        h_step=1;
//        record[0][0] = m,record[0][1] = n;

    h_step=BFS(start);

        //按求出的行走路线，将数字1, 2, 3,…,64依次填入一个8×8的方阵，输出
//        for(int i=0;i<MAXN;i++){
//            qDebug("%3d%3d%3d%3d%3d%3d%3d%3d",
//                   map[i][0],map[i][1],map[i][2],map[i][3],
//                   map[i][4],map[i][5],map[i][6],map[i][7]);//QDebug自带换行,所以一次性输出一行
//        }
//        qDebug("step=%d.\n",h_step);
//        qDebug("\n");
//    }

    //打印路径
//    for(int i=0;i<64;i++){
//        qDebug("%3d%3d",record[i][0],record[i][1]);
//    }
//    return 0;


//12.7//先执行完算法保存结果在map和record中，再进行绘制，下面的while循环中便于增加信号量锁并保存中间结果

    if (flag_loadBtn_start ==1 )
    {
        h_step = loadstep;
        while(h_step < 64)
        {
            pause.lock();
            QPainter *painter = new QPainter;
            msleep(m_runFrame);// 修改此处设置刷新频率
            h_step ++;
            pause.unlock();
        }
    }
    else
    {
        h_step=1;
        while(h_step < 64)
        {
            pause.lock();
            QPainter *painter = new QPainter;
            msleep(m_runFrame);// 修改此处设置刷新频率
            h_step ++;
            pause.unlock();
        }
    }

    // 执行完等待用户按停止才能开始下一次，此处可以继续完善进入KeyEvent::slotStop()

}

Horse::Horse()
{
    for(int i=0;i<64;i++){
        this->record[i][0] = 0;
        this->record[i][1] = 0;
    }

    this->iX = 0;
    this->iY = 0;


    this->h_step = 0;//记录马走的步数
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            this->map[i][j] = 0;//8*8的国际象棋棋盘
        }
    }

    this->m_runFrame = 100;

}

//void Horse::run()
//{
//    this->work();
//}

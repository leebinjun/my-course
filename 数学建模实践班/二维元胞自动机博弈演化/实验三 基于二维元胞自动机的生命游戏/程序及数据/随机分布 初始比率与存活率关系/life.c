#include<stdio.h>
#include<time.h>


#define STEP 5000        //演化步
/*声明生命图大小*/
#define MAXROW 100       //行数
#define MAXCOL 100       //列数
/*声明个体状态*/
#define DEAD 0
#define ALIVE 1

int map[MAXROW][MAXCOL],newmap[MAXROW][MAXCOL];
float ave;
float p;            //初始时存活个体的比例

void init();                              //初始化
int neighbors(int,int);                   //计算邻居数量
int count(int map[MAXROW][MAXCOL]);       //计算存活个体的数量

void main()
{
    int r,c,t;
    FILE *fp;
    fp=fopen("data.txt","w");
for(p=0.00;p<1;p+=0.02)
{
    printf("p=%f\n",p);
    init();
    printf("init is over\n");                                  //初始化
    for(t=1;t<=STEP;t++)                       //演化
    {
        for(r=0;r<MAXROW;r++)
            for(c=0;c<MAXCOL;c++)
                switch (neighbors(r,c))        //规则判断
                {
                    case 0:
                    case 1:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    newmap[r][c]=DEAD;
                    break;
                    case 2:
                    newmap[r][c]=map[r][c];
                    break;
                    case 3:
                    newmap[r][c]=ALIVE;
                    break;
                }
        for(r=0;r<MAXROW;r++)                   //生成新生命图
        {
            for(c=0;c<MAXCOL;c++)
            {
                map[r][c]=newmap[r][c];
  //              fprintf(fp1,"%d ",map[r][c]);
            }
        }
    }
    ave=(float)count(map)/(MAXCOL*MAXROW);//计算存活个体的比率并输出
    fprintf(fp,"%f %f\n",p,ave);
    printf("%f %f\n",p,ave);
}
}


void init()                //初始化
{
    int r,c,i;
	for(r=0;r<MAXROW;r++)               //先令所有个体状态为死亡
        for(c=0;c<MAXCOL;c++)
        {map[r][c]=DEAD;}
    srand((unsigned)time(NULL));        //“撒种子”
    for(i=p*MAXCOL*MAXROW;i>0;i--)      //为减少运算，先进行P*MAXCOL*MAXROW次随机赋值
    {
        c=rand()%MAXCOL;
        r=rand()%MAXROW;                //随机选择个体
	    map[c][r]=ALIVE;                //令该个体状态为存活
    }
    while(count(map)<=p*MAXCOL*MAXROW)  //当存活个体达到比率P，结束赋值
	{
	    c=rand()%MAXCOL;
        r=rand()%MAXROW;                //随机选择个体
	    map[c][r]=ALIVE;                //令该个体状态为存活
	}
}

int neighbors(int row,int col)          //计算邻居数
{
    int count=0,c,r;
    for(r=row-1;r<=row+1;r++)
        for(c=col-1;c<=col+1;c++)
        {
            if(map[(r+MAXROW)%MAXROW][(c+MAXCOL)%MAXCOL]==ALIVE)
            count++;
        }
    if(map[row][col]==ALIVE)
        count--;
    return count;
}

int count(int map[MAXROW][MAXCOL])      //计算存活的个体数
{
    int r,c,n=0;
    for(r=0;r<MAXROW;r++)
        for(c=0;c<MAXCOL;c++)
        {n+=map[r][c];}
    return n;
}

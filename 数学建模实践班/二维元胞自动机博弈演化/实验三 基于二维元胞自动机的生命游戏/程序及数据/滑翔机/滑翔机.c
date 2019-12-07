#include<stdio.h>
#include<time.h>

//#define P 0.7            //初始时存活个体的比例
#define STEP 1000        //演化步
/*声明生命图大小*/
#define MAXROW 40       //行数
#define MAXCOL 30       //列数
/*声明个体状态*/
#define DEAD 0
#define ALIVE 1

int map[MAXROW][MAXCOL],newmap[MAXROW][MAXCOL];
float ave[STEP];

void init();                              //初始化
int neighbors(int,int);                   //计算邻居数量
int count(int map[MAXROW][MAXCOL]);       //计算存活个体的数量

void main()
{
    int r,c,t;
    FILE *fp1;
    FILE *fp2;

    fp1=fopen("map.txt","w");
    fp2=fopen("data.txt","w");

    init();
     for(r=0;r<MAXROW;r++)                   //输出生命图
        {
            for(c=0;c<MAXCOL;c++)
            {
			//	printf("%d",map[r][c]);
                fprintf(fp1,"%d ",map[r][c]);
            }
        fprintf(fp1,"\n");
        }                                //初始化
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
        for(r=0;r<MAXROW;r++)                   //输出生命图
        {
            for(c=0;c<MAXCOL;c++)
            {
                map[r][c]=newmap[r][c];
			//	printf("%d",map[r][c]);
                fprintf(fp1,"%d ",map[r][c]);
            }
        fprintf(fp1,"\n");
        }
        ave[t]=(float)count(map)/(MAXCOL*MAXROW);//计算存活个体的比率并输出
        fprintf(fp2,"%f\n",ave[t]);
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


void init()                //初始化
{
    int r,c,i;
	for(r=0;r<MAXROW;r++)               //先令所有个体状态为死亡
        for(c=0;c<MAXCOL;c++)
        {map[r][c]=DEAD;}
//    srand((unsigned)time(NULL));        //“撒种子”
//    for(i=P*MAXCOL*MAXROW;i>0;i--)      //为减少运算，先进行P*MAXCOL*MAXROW次随机赋值
//    {
//        c=rand()%MAXCOL;
//        r=rand()%MAXROW;                //随机选择个体
//	    map[c][r]=ALIVE;                //令该个体状态为存活
//    }
//    while(count(map)!=P*MAXCOL*MAXROW)  //当存活个体达到比率P，结束赋值
//	{
//	    c=rand()%MAXCOL;
//        r=rand()%MAXROW;                //随机选择个体
//	    map[c][r]=ALIVE;                //令该个体状态为存活
//	}


			map[0][23]=map[0][24]=ALIVE;
			map[1][23]=map[1][24]=ALIVE;
			map[2][10]=map[2][15]=map[2][27]=map[2][26]=ALIVE;
			map[3][8]=map[3][10]=map[3][15]=map[3][26]=map[3][27]=map[3][28]=map[3][34]=map[3][35]=ALIVE;
		    map[4][6]=map[4][7]=map[4][15]=map[4][26]=map[4][27]=map[4][34]=map[4][35]=ALIVE;
			map[5][0]=map[5][1]=map[5][6]=map[5][7]=map[5][19]=map[5][20]=map[5][23]=map[5][24]=ALIVE;
		    map[6][0]=map[6][1]=map[6][6]=map[6][7]=map[6][16]=map[6][17]=map[6][20]=map[6][23]=map[6][24]=ALIVE;
			map[7][8]=map[7][10]=map[7][16]=map[7][17]=map[7][18]=map[7][19]=ALIVE;
            map[8][10]=map[8][18]=ALIVE;


}

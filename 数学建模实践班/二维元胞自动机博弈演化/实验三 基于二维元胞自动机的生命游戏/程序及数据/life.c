#include<stdio.h>
#include<time.h>

#define P 0.7            //��ʼʱ������ı���
#define STEP 2500        //�ݻ���
/*��������ͼ��С*/
#define MAXROW 100       //����
#define MAXCOL 100       //����
/*��������״̬*/
#define DEAD 0
#define ALIVE 1

int map[MAXROW][MAXCOL],newmap[MAXROW][MAXCOL];
float ave[STEP];

void init();                              //��ʼ��
int neighbors(int,int);                   //�����ھ�����
int count(int map[MAXROW][MAXCOL]);       //��������������

void main()
{
    int r,c,t;
    FILE *fp1;
    FILE *fp2;

    fp1=fopen("map.txt","w");
    fp2=fopen("data.txt","w");

    init();                                    //��ʼ��
    for(t=1;t<=STEP;t++)                       //�ݻ�
    {
        for(r=0;r<MAXROW;r++)
            for(c=0;c<MAXCOL;c++)
                switch (neighbors(r,c))        //�����ж�
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
        for(r=0;r<MAXROW;r++)                   //�������ͼ
        {
            for(c=0;c<MAXCOL;c++)
            {
                map[r][c]=newmap[r][c];
                fprintf(fp1,"%d ",map[r][c]);
            }
        fprintf(fp1,"\n");
        }
        ave[t]=(float)count(map)/(MAXCOL*MAXROW);//���������ı��ʲ����
        fprintf(fp2,"%f\n",ave[t]);
    }
}

void init()                //��ʼ��
{
    int r,c,i;
	for(r=0;r<MAXROW;r++)               //�������и���״̬Ϊ����
        for(c=0;c<MAXCOL;c++)
        {map[r][c]=DEAD;}
    srand((unsigned)time(NULL));        //�������ӡ�
    for(i=P*MAXCOL*MAXROW;i>0;i--)      //Ϊ�������㣬�Ƚ���P*MAXCOL*MAXROW�������ֵ
    {
        c=rand()%MAXCOL;
        r=rand()%MAXROW;                //���ѡ�����
	    map[c][r]=ALIVE;                //��ø���״̬Ϊ���
    }
    while(count(map)!=P*MAXCOL*MAXROW)  //��������ﵽ����P��������ֵ
	{
	    c=rand()%MAXCOL;
        r=rand()%MAXROW;                //���ѡ�����
	    map[c][r]=ALIVE;                //��ø���״̬Ϊ���
	}
}

int neighbors(int row,int col)          //�����ھ���
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

int count(int map[MAXROW][MAXCOL])      //������ĸ�����
{
    int r,c,n=0;
    for(r=0;r<MAXROW;r++)
        for(c=0;c<MAXCOL;c++)
        {n+=map[r][c];}
    return n;
}

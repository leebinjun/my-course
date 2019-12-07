#include<stdio.h>
#include<time.h>

//#define P 0.7            //��ʼʱ������ı���
#define STEP 1000        //�ݻ���
/*��������ͼ��С*/
#define MAXROW 40       //����
#define MAXCOL 30       //����
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

    init();
     for(r=0;r<MAXROW;r++)                   //�������ͼ
        {
            for(c=0;c<MAXCOL;c++)
            {
			//	printf("%d",map[r][c]);
                fprintf(fp1,"%d ",map[r][c]);
            }
        fprintf(fp1,"\n");
        }                                //��ʼ��
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
			//	printf("%d",map[r][c]);
                fprintf(fp1,"%d ",map[r][c]);
            }
        fprintf(fp1,"\n");
        }
        ave[t]=(float)count(map)/(MAXCOL*MAXROW);//���������ı��ʲ����
        fprintf(fp2,"%f\n",ave[t]);
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


void init()                //��ʼ��
{
    int r,c,i;
	for(r=0;r<MAXROW;r++)               //�������и���״̬Ϊ����
        for(c=0;c<MAXCOL;c++)
        {map[r][c]=DEAD;}
//    srand((unsigned)time(NULL));        //�������ӡ�
//    for(i=P*MAXCOL*MAXROW;i>0;i--)      //Ϊ�������㣬�Ƚ���P*MAXCOL*MAXROW�������ֵ
//    {
//        c=rand()%MAXCOL;
//        r=rand()%MAXROW;                //���ѡ�����
//	    map[c][r]=ALIVE;                //��ø���״̬Ϊ���
//    }
//    while(count(map)!=P*MAXCOL*MAXROW)  //��������ﵽ����P��������ֵ
//	{
//	    c=rand()%MAXCOL;
//        r=rand()%MAXROW;                //���ѡ�����
//	    map[c][r]=ALIVE;                //��ø���״̬Ϊ���
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

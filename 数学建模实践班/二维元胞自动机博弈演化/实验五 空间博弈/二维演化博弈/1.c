#include<stdlib.h>
#include<stdio.h>
#define L 100               //游戏规模
#define step 300            //演化步
#define B 1.93              //背叛诱惑

void main()
{
    int a[L][L],b[L][L];     //策略时空图  strange
    float p[L][L];        //收益时空图  payoff
    int c[L][L];             //变化时空图  changes  0>0:1 0>1:2 1>0:3 1>1:4
    float fc=0;              //合作频率

    int tmp_m;               //临时变量用于存放取得最大收益的策略
    float tmp_n;                //临时变量用于存放最大收益值
    int i,j,t,count=0;

    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("strange.txt","w");
    fp2=fopen("payoff.txt","w");
    fp3=fopen("change.txt","w");
    fp4=fopen("fc.txt","w");

//    for(i=0;i<L;i++)                //赋初值
//        for(j=0;j<L;j++)
//            a[i][j]=b[i][j]=1;
//    a[49][49]=b[49][49]=0;

    for(i=0;i<L;i++)                //赋初值
        for(j=0;j<L;j++)
            {
                switch(rand()%10)
                {
                    case 0:case 1:case 2:case 3:
                        a[i][j]=b[i][j]=0;
                        break;
                    default:
                        a[i][j]=b[i][j]=1;
                }
            }

    for(t=0;t<step;t++)
    {
        for(i=0;i<L;i++)
        {
            for(j=0;j<L;j++)
            {
                count=0;
                if(a[(i-1+L)%L][(j-1+L)%L]==1) count++;
                if(a[(i-1+L)%L][j]==1) count++;
                if(a[(i-1+L)%L][(j+1+L)%L]==1) count++;
                if(a[i][(j-1+L)%L]==1) count++;
                if(a[i][j]==1) count++;
                if(a[i][(j+1+L)%L]==1) count++;
                if(a[(i+1+L)%L][(j-1+L)%L]==1) count++;
                if(a[(i+1+L)%L][j]==1) count++;
                if(a[(i+1+L)%L][(j+1+L)%L]==1) count++;

                if(a[i][j]==1)
                    p[i][j]=1*count;
                else
                    p[i][j]=B*count;                //计算收益

                fprintf(fp2,"%3.2f ",p[i][j]);
            }
            fprintf(fp2,"\n");
        }
        for(i=0;i<L;i++)
        {
            for(j=0;j<L;j++)
            {
                tmp_n=0;
                tmp_m=0;

                if(p[(i-1+L)%L][(j-1+L)%L]>tmp_n) tmp_n=p[(i-1+L)%L][(j-1+L)%L],tmp_m=a[(i-1+L)%L][(j-1+L)%L];
                if(p[(i-1+L)%L][j]>tmp_n) tmp_n=p[(i-1+L)%L][j],tmp_m=a[(i-1+L)%L][j];
                if(p[(i-1+L)%L][(j+1+L)%L]>tmp_n) tmp_n=p[(i-1+L)%L][(j+1+L)%L],tmp_m=a[(i-1+L)%L][(j+1+L)%L];
                if(p[i][(j-1+L)%L]>tmp_n) tmp_n=p[i][(j-1+L)%L],tmp_m=a[i][(j-1+L)%L];
                if(p[i][j]>tmp_n) tmp_n=p[i][j],tmp_m=a[i][j];
                if(p[i][(j+1+L)%L]>tmp_n) tmp_n=p[i][(j+1+L)%L],tmp_m=a[i][(j+1+L)%L];
                if(p[(i+1+L)%L][(j-1+L)%L]>tmp_n) tmp_n=p[(i+1+L)%L][(j-1+L)%L], tmp_m=a[(i+1+L)%L][(j-1+L)%L];
                if(p[(i+1+L)%L][j]>tmp_n) tmp_n=p[(i+1+L)%L][j],tmp_m=a[(i+1+L)%L][j];
                if(p[(i+1+L)%L][(j+1+L)%L]>tmp_n) tmp_n=p[(i+1+L)%L][(j+1+L)%L],tmp_m=a[(i+1+L)%L][(j+1+L)%L];

                b[i][j]=tmp_m;
            }
        }

        for(i=0;i<L;i++)                       //统计策略变化情况
        {
            for(j=0;j<L;j++)
            {
                if (a[i][j]==0&&b[i][j]==0)
                    c[i][j]=1;
                else if (a[i][j]==0&&b[i][j]==1)
                    c[i][j]=2;
                else if (a[i][j]==1&&b[i][j]==0)
                    c[i][j]=3;
                else if(a[i][j]==1&&b[i][j]==1)
                    c[i][j]=4;
                a[i][j]=b[i][j];

            fprintf(fp1,"%d ",a[i][j]);
            fprintf(fp3,"%d ",c[i][j]);
            }
            fprintf(fp1,"\n");
            fprintf(fp3,"\n");
        }

        count=0;                    //计算合作频率
        for(i=0;i<L;i++)
            for(j=0;j<L;j++)
                count+=a[i][j];
        fc=(float)count/10000;
        printf("%lf",fc);
        fprintf(fp4,"%lf\n",fc);

        fprintf(fp1,"\n");
        fprintf(fp2,"\n");
        fprintf(fp3,"\n");
    }
}

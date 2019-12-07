#include<stdlib.h>
#define L 100                //参与人数 numbers who joins the game
#define step 200            //演化步
#define B 1.93              //背叛诱惑
#include<stdio.h>
void main()
{
    int a[L][L],b[L][L];     //策略时空图  strange
    float p[L][L],n;           //收益时空图  payoff
    int c[L][L];             //变化时空图  changes  0>0:1 0>1:2 1>0:3 1>1:4

    int i,j,k,count=0,m;
    FILE *fp1,*fp2,*fp3;


    printf("input any char to begin:");
    getchar();

   // fp2=fopen("a.txt","w");
  //  fp1=fopen("p.txt","w");
    fp3=fopen("c.txt","w");
    for(i=0;i<L;i++)                //赋初值
        for(j=0;j<L;j++)
            a[i][j]=b[i][j]=1;
    a[L/2][L/2]=b[L/2][L/2]=0;

for(k=0;k<step;k++){
    for(i=0;i<L;i++)
        {
        for(j=0;j<L;j++)
            {
//                p[i][j]=cout(a[j][k]);
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

                count=0;
        //       printf("%3.2f ",p[i][j]);                //
         //      fprintf(fp1,"%3.2f ",p[i][j]);



            }
       //   printf("\n");
       //   fprintf(fp1,"\n");
}
 for(i=0;i<L;i++)
        {
        for(j=0;j<L;j++)
            {
                n=0;
                m=0;

                if(p[(i-1+L)%L][(j-1+L)%L]>n) n=p[(i-1+L)%L][(j-1+L)%L],m=a[(i-1+L)%L][(j-1+L)%L];
                if(p[(i-1+L)%L][j]>n) n=p[(i-1+L)%L][j],m=a[(i-1+L)%L][j];
                if(p[(i-1+L)%L][(j+1+L)%L]>n) n=p[(i-1+L)%L][(j+1+L)%L],m=a[(i-1+L)%L][(j+1+L)%L];
                if(p[i][(j-1+L)%L]>n) n=p[i][(j-1+L)%L],m=a[i][(j-1+L)%L];
                if(p[i][j]>n) n=p[i][j],m=a[i][j];
                if(p[i][(j+1+L)%L]>n) n=p[i][(j+1+L)%L],m=a[i][(j+1+L)%L];
                if(p[(i+1+L)%L][(j-1+L)%L]>n) n=p[(i+1+L)%L][(j-1+L)%L], m=a[(i+1+L)%L][(j-1+L)%L];
                if(p[(i+1+L)%L][j]>n) n=p[(i+1+L)%L][j],m=a[(i+1+L)%L][j];
                if(p[(i+1+L)%L][(j+1+L)%L]>n) n=p[(i+1+L)%L][(j+1+L)%L],m=a[(i+1+L)%L][(j+1+L)%L];

                b[i][j]=m;
            }
                }

       for(i=0;i<L;i++)
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
        //    printf("%d ",a[i][j]);
       //     fprintf(fp2,"%d ",a[i][j]);
            fprintf(fp3,"%d ",c[i][j]);
            }
//printf("\n");
//fprintf(fp2,"\n");
fprintf(fp3,"\n");
}
//printf("\n");
//fprintf(fp1,"\n");
//fprintf(fp2,"\n");
//fprintf(fp3,"\n");
}
}

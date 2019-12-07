#include<stdio.h>
#include<stdlib.h>

#define L 100
#define step 100

void main()
{
    FILE *fp;
    int time,i,j,n;
    int a[L],b[L];
    int r[8],r1[8],r2[8],r3[8];

    if((fp=fopen("时空图.txt","w"))==NULL)
    {
        printf("Error!can't open\n");
        exit(0);
    }

    printf("确定输出为‘1’的函数种类(n<=8)：");   //定义规则
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("函数%d为",i);
        scanf("%d %d %d",&r1[i],&r2[i],&r3[i]);
        r[i]=4*r1[i]+2*r2[i]+1*r3[i];
    }

    for(i=0;i<L;i++)           //赋初值
    {
        a[i]=b[i]=0;
    }
    a[L/2]=b[L/2]=1;

    printf("时空图：\n");
    for(i=0;i<L;i++)                   //输出初始值
    {
        printf("%d",a[i]);
        fprintf(fp,"%d ",a[i]);
    }
    printf("\n");
    fputs("\n",fp);

    for(time=0;time<step;time++)                    //循环1实现输出100步
    {
        for(j=0;j<L;j++)                          //循环2实现输出下一步
        {
            for(i=1;i<=n;i++)                       //使用n种函数规则依次判断
            {
                if(4*a[(j+L-1)%L]+2*a[j]+1*a[(j+L+1)%L]==r[i])       //规则判断
                {
                    b[j]=1;
                    break;                       //一旦符合跳出规则判断循环
                }
                else
                b[j]=0;
            }
        }

        for(i=0;i<L;i++)                          //输出下一步
		{
            a[i]=b[i];
            printf("%d",a[i]);
            fprintf(fp,"%d ",a[i]);
		}
        printf("\n");
        fprintf(fp,"\n");
    }
    fclose(fp);
}

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

    if((fp=fopen("ʱ��ͼ.txt","w"))==NULL)
    {
        printf("Error!can't open\n");
        exit(0);
    }

    printf("ȷ�����Ϊ��1���ĺ�������(n<=8)��");   //�������
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("����%dΪ",i);
        scanf("%d %d %d",&r1[i],&r2[i],&r3[i]);
        r[i]=4*r1[i]+2*r2[i]+1*r3[i];
    }

    for(i=0;i<L;i++)           //����ֵ
    {
        a[i]=b[i]=0;
    }
    a[L/2]=b[L/2]=1;

    printf("ʱ��ͼ��\n");
    for(i=0;i<L;i++)                   //�����ʼֵ
    {
        printf("%d",a[i]);
        fprintf(fp,"%d ",a[i]);
    }
    printf("\n");
    fputs("\n",fp);

    for(time=0;time<step;time++)                    //ѭ��1ʵ�����100��
    {
        for(j=0;j<L;j++)                          //ѭ��2ʵ�������һ��
        {
            for(i=1;i<=n;i++)                       //ʹ��n�ֺ������������ж�
            {
                if(4*a[(j+L-1)%L]+2*a[j]+1*a[(j+L+1)%L]==r[i])       //�����ж�
                {
                    b[j]=1;
                    break;                       //һ���������������ж�ѭ��
                }
                else
                b[j]=0;
            }
        }

        for(i=0;i<L;i++)                          //�����һ��
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

//#include<iostream>
//#include<time.h>
//#include<stdlib.h>
//#include<stdio.h>
//using namespace std;
//
//const int popsize=100;//��Ⱥ��ģ
//const double pc=0.6;//�������
//const double pm=0.01;//�������
//const int lchrom=32;//Ⱦɫ�峤��
//const int maxgen=3000;//����������
//
//struct population
//{
//	unsigned int chrom[lchrom];//Ⱦɫ��
//	double weight;//��������
//	double volume;//�������
//	double fitness;//��Ӧ��
//	unsigned int parent1,parent2,cross;//˫�ס������
//};
//
////��������Ⱥ��������Ⱥ
//struct population oldpop[popsize],newpop[popsize];
////����������������������ֵ����������
//int weight[lchrom]={22,15, 4, 5,10,19,21,20, 8,13, 2, 3, 3,17,12, 5,12, 4, 1,21,14,23,17,15,20,22,25, 0,22,15,25,13};
//int volume[lchrom]={11,22,12,21,21,13, 1,10,13, 8, 6,25,13,27,12,23,12,24,23,11, 6,24,28,10,20,13,25,23, 5,26,30,15};
//int profit[lchrom]={ 8, 9,15, 6,16, 9, 1, 4,14, 9, 3, 7,12, 4,15, 5,18, 5,15, 4, 6, 2,12,14,11, 9,13,13,14,13,19, 4};
//int contain_weight=80;
//int contain_volume=75;
////��Ⱥ������Ӧ�ȡ���С�����ƽ����Ӧ��
//double sumfitness,minfitness,curmaxfitness,avgfitness,maxfitness;
////һ����Ⱥ��������С��Ӧ�ȵĸ���
//int minpop,maxpop;
//
////������Ⱥ�и�������
//double cal_weight(unsigned int *chr)
//{
//	int j;
//	double pop_weight;
//	pop_weight=0;
//	for(j=0;j<lchrom;j++)
//	{
//		pop_weight=pop_weight+(*chr)*weight[j];
//		chr++;
//	}
//	return pop_weight;
//}
//
////������Ⱥ�и������
//double cal_volume(unsigned int *chr)
//{
//	int j;
//	double pop_volume;
//	pop_volume=0;
//	for(j=0;j<lchrom;j++)
//	{
//		pop_volume=pop_volume+(*chr)*volume[j];
//		chr++;
//	}
//	return pop_volume;
//}
//
////������Ⱥ�и�����Ӧ��
//double cal_fit(unsigned int *chr)
//{
//	int j;
//	double pop_profit;
//	pop_profit=0;
//	for(j=0;j<lchrom;j++)
//	{
//		pop_profit=pop_profit+(*chr)*profit[j];
//		chr++;
//	}
//	return pop_profit;
//}
//
////ͳ����Ӧ�ȵ������Сֵ��������Ϣ
//void statistics(struct population *pop)
//{
//	int i;
//	double tmp_fit;
//	sumfitness=pop[0].fitness;
//	minfitness=pop[0].fitness;
//	minpop=0;
//	curmaxfitness=pop[0].fitness;
//	maxpop=0;
//	for(i=1;i<popsize;i++)
//	{
//		sumfitness=sumfitness+pop[i].fitness;
//		tmp_fit=pop[i].fitness;
//		if(tmp_fit>curmaxfitness)
//		{
//			curmaxfitness=pop[i].fitness;
//			maxpop=i;
//		}
//		if(tmp_fit<minfitness)
//		{
//			minfitness=pop[i].fitness;
//			minpop=i;
//		}
//	}
//	if(curmaxfitness>maxfitness)
//	{
//		maxfitness=curmaxfitness;
//	}
//	avgfitness=sumfitness/(float)popsize;
//}
//
////������Ⱥ��Ϣ
//void report(struct population *pop,int gen)
//{
//	int j;
//	int pop_weight = 0;
//	int pop_volume = 0;
//	cout<<endl<<"the generation is "<<gen<<endl;
//	cout<<"the population's chrom is:";
//	for(j=0;j<lchrom;j++)
//	{
//		if(j%5==0)
//		{
//			cout<<"  ";
//		}
//		cout<<pop[maxpop].chrom[j];
//	}
//	cout<<endl<<"parent is "<<(int)pop[maxpop].parent1<<" and "<<(int)pop[maxpop].parent2<<endl;
//	cout<<"cross position is "<<(int)pop[maxpop].cross;
//	cout<<endl<<"The population's max fitness is "<<(int)pop[maxpop].fitness;
//	cout<<endl<<"The knapsack weight is "<<(int)pop[maxpop].weight;
//    cout<<endl<<"The knapsack volume is "<<(int)pop[maxpop].volume<<endl;
//}
//
////��ʼ����Ⱥ
//void initpop()
//{
//	int i,j,ispop;
//	double tmpweight,tmpvolume;
//	ispop=false;
//	maxfitness=0;
//	for(i=0;i<popsize;i++)
//	{
//		while(!ispop)
//		{
//			for(j=0;j<lchrom;j++)
//			{
//				oldpop[i].chrom[j]=rand()%2;
//			}
//            //ѡ������С�ڱ��������ĸ���
//			tmpweight=cal_weight(oldpop[i].chrom);
//            //tmpvolume=cal_volume(oldpop[i].chrom);
//			if((tmpweight<=contain_weight) && (tmpvolume<=contain_volume))
//			{
//				oldpop[i].fitness=cal_fit(oldpop[i].chrom);
//				oldpop[i].weight=tmpweight;
//				oldpop[i].volume=tmpvolume;
//				oldpop[i].parent1=0;
//				oldpop[i].parent2=0;
//				oldpop[i].cross=0;
//				ispop=true;
//			}
//		}
//		ispop=false;
//	}
//}
//
////ѡ��
//int selection(int pop)
//{
//	double wheel_pos,rand_number,partsum;
//	int parent;
//	//���ַ�
//	rand_number=(rand()%2001)/2000.0;
//	wheel_pos=rand_number*sumfitness;
//	partsum=0;
//	parent=0;
//	do{
//		partsum=partsum+oldpop[parent].fitness;
//		parent=parent+1;
//	}while(partsum<wheel_pos&&parent<popsize);
//	return parent-1;
//}
//
////����ѡ������
//int execise(double probability)
//{
//	double pp;
//	pp=(double)((rand()%20001)/20000.0);
//	if(pp<probability) return 1;
//	return 0;
//}
//
////����
//int crossover(unsigned int *parent1,unsigned int *parent2,int i)
//{
//	int j,cross_pos;
//	if(execise(pc))
//	{
//		cross_pos=rand()%(lchrom-1);
//	}
//	else cross_pos=lchrom-1;
//	for(j=0;j<=cross_pos;j++)
//	{
//		newpop[i].chrom[j]=parent1[j];
//	}
//	for(j=cross_pos+1;j<lchrom;j++)
//	{
//		newpop[i].chrom[j]=parent2[j];
//	}
//	newpop[i].cross=cross_pos;
//	return 1;
//}
//
////����
//int mutation(unsigned int alleles)
//{
//	if(execise(pm))
//	{
//		if(alleles)
//			alleles=0;
//		else alleles=1;
//	}
//	return alleles;
//}
//
////Ⱥ�����
//void generation()
//{
//	unsigned int i,j,mate1,mate2;
//	double tmpweight,tmpvolume;
//	int ispop;
//	i=0;
//	while(i<popsize)
//	{
//		ispop=false;
//		while(!ispop)
//		{
//			//ѡ��
//			mate1=selection(i);
//			mate2=selection(i+1);
//			//����
//			crossover(oldpop[mate1].chrom,oldpop[mate2].chrom,i);
//			//����
//			for(j=0;j<lchrom;j++)
//			{
//				newpop[i].chrom[j]=mutation(newpop[i].chrom[j]);
//			}
//			//ѡ������С�ڱ��������ĸ���
//			tmpweight=cal_weight(newpop[i].chrom);
//            tmpvolume=cal_volume(newpop[i].chrom);
//			if((tmpweight<=contain_weight) && (tmpvolume<=contain_volume))
//			{
//				newpop[i].fitness=cal_fit(newpop[i].chrom);
//				newpop[i].weight=tmpweight;
// 				newpop[i].volume=tmpvolume;
//				newpop[i].parent1=mate1;
//				newpop[i].parent2=mate2;
//				ispop=true;
//			}
//		}
//		i=i+1;
//	}
//}
//
//int main()
//{
//	int gen,oldmaxpop,k,randpos;
//	double oldmax;
//	gen=0;
//	srand((unsigned)time(NULL));
//	initpop();
//	for(k=0;k<popsize;k++)
//		newpop[k]=oldpop[k];
//	statistics(newpop);
//	report(newpop,gen);
//	while(gen<maxgen)
//	{
//		gen=gen+1;
//		if(gen%100==0)
//			srand((unsigned)time(NULL));
//		oldmax=curmaxfitness;
//		oldmaxpop=maxpop;
//		generation();
//		statistics(newpop);
//		if(curmaxfitness<oldmax)
//		{
//			randpos=rand()%popsize;
//			for(k=0;k<lchrom;k++)
//				newpop[randpos].chrom[k]=oldpop[oldmaxpop].chrom[k];
//			newpop[randpos].fitness=oldpop[oldmaxpop].fitness ;
//			newpop[randpos].weight=oldpop[oldmaxpop].weight ;
//            newpop[randpos].volume=oldpop[oldmaxpop].volume ;
//			newpop[randpos].parent1 =oldpop[oldmaxpop].parent1 ;
//			newpop[randpos].parent2 =oldpop[oldmaxpop].parent2;
//			newpop[randpos].cross =oldpop[oldmaxpop].cross;
//			statistics(newpop);
//		}
//		else if(curmaxfitness>oldmax)
//		{
//			report(newpop,gen);
//		}
//		for(k=0;k<popsize;k++)
//			oldpop[k]=newpop[k];
//	}
//
//	cout<<endl<<"It's over!"<<endl;
//
//	if (newpop[maxpop].fitness != 97)
//    {
//        cout << "the result should be 97" << endl;
//        cout << "bad luck, please try again!" << endl;
//    }
//
//	system("pause");
//
//    return 0;
//}

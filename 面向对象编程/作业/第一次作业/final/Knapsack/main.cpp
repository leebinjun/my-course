#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

const int popsize = 100;    // 种群规模
const double pc = 0.6;      // 交叉概率
const double pm = 0.01;     // 变异概率
const int lchrom = 32;      // 染色体长度
const int maxgen = 100;     // 最大进化代数

class CGeneAlgoOperater{

private:
    struct population {
        unsigned int chrom[lchrom];             // 染色体
        double weight;//背包重量
        double volume;//背包体积
        double fitness;//适应度
        unsigned int parent1,parent2,cross;     // 双亲、交叉点
    };
    // 新生代种群、父代种群
    struct population oldpop[popsize],newpop[popsize];
    // 背包问题各个物体重量、体积、价值
    int weight[lchrom] = {0};
    int volume[lchrom] = {0};
    int profit[lchrom] = {0};
    // 背包重量、体积最大限制
    int contain_weight;
    int contain_volume;
    // 种群的总适应度、最小、最大、平均适应度
    double sumfitness,minfitness,curmaxfitness,avgfitness,maxfitness;
    // 一个种群中最大和最小适应度的个体
    int minpop,maxpop;

public:
    // 构造函数，传入背包重量、体积限制和物品重量、体积、价值数据
    CGeneAlgoOperater(int x_weight, int x_volume, int *x_aweight, int *x_avolume, int *x_aprofit) {
        contain_weight = x_weight;
        contain_volume = x_volume;
        for (int i = 0; i < lchrom; i++) {
            weight[i]=x_aweight[i];
            volume[i]=x_avolume[i];
            profit[i]=x_aprofit[i];
        }
    }

private:
    // 计算物品的总重量
    double cal_weight(unsigned int *chr) {
        int j;
        double pop_weight;
        pop_weight=0;
        for(j=0;j<lchrom;j++) {
            pop_weight=pop_weight+(*chr)*weight[j];
            chr++;
        }
        return pop_weight;
    }

    // 计算物品的总体积
    double cal_volume(unsigned int *chr) {
        int j;
        double pop_volume;
        pop_volume=0;
        for(j=0;j<lchrom;j++) {
            pop_volume=pop_volume+(*chr)*volume[j];
            chr++;
        }
        return pop_volume;
    }

    // 计算物品放的总价值
    double cal_fit(unsigned int *chr) {
        int j;
        double pop_profit;
        pop_profit=0;
        for(j=0;j<lchrom;j++) {
            pop_profit=pop_profit+(*chr)*profit[j];
            chr++;
        }
        return pop_profit;
    }

    // 统计适应度的最大、最小值及其他信息
    void statistics(struct population *pop) {
        int i;
        double tmp_fit;
        sumfitness=pop[0].fitness;
        minfitness=pop[0].fitness;
        minpop=0;
        curmaxfitness=pop[0].fitness;
        maxpop=0;
        for(i=1;i<popsize;i++) {
            sumfitness=sumfitness+pop[i].fitness;
            tmp_fit=pop[i].fitness;
            if(tmp_fit>curmaxfitness) {
                curmaxfitness=pop[i].fitness;
                maxpop=i;
            }
            if(tmp_fit<minfitness) {
                minfitness=pop[i].fitness;
                minpop=i;
            }
        }
        if(curmaxfitness>maxfitness) {
            maxfitness=curmaxfitness;
        }
        avgfitness=sumfitness/(float)popsize;
    }

    //报告种群信息
    void report(struct population *pop,int gen) {
        int j;
        int pop_weight = 0;
        int pop_volume = 0;
        cout<<endl<<"the generation is "<<gen<<endl;

        //cout<<"the population's chrom is:";   // 打印选择的物品号码
        cout<<"the goods' number is:";   // 打印选择的物品号码
        for(j=0;j<lchrom;j++) {
//            if(j%5==0){
//                cout<<"  ";
//            }
//            cout<<pop[maxpop].chrom[j];
            if(pop[maxpop].chrom[j] != 0)
                cout << ' ' << j;
        }
        //cout<<endl<<"parent is "<<(int)pop[maxpop].parent1<<" and "<<(int)pop[maxpop].parent2<<endl;
        //cout<<"cross position is "<<(int)pop[maxpop].cross;
        cout<<endl<<"The goods' max value is "<<(int)pop[maxpop].fitness;
        cout<<endl<<"The knapsack weight is "<<(int)pop[maxpop].weight;
        cout<<endl<<"The knapsack volume is "<<(int)pop[maxpop].volume<<endl;
    }

    //初始化种群
    void initpop() {
        int i,j,ispop;
        double tmpweight,tmpvolume;
        ispop=false;
        maxfitness=0;
        for(i=0;i<popsize;i++) {
            while(!ispop) {
                for(j=0;j<lchrom;j++) {
                    int tempp = rand()%4;          // 此处调低生成字符1的比例为25%，否则容易跑死
                    if( tempp == 1) {
                        oldpop[i].chrom[j]=1;
                    } else {
                        oldpop[i].chrom[j]=0;
                    }
                }
                //选择重量小于背包容量的个体
                tmpweight=cal_weight(oldpop[i].chrom);
                //cout << tmpweight << endl;
                tmpvolume=cal_volume(oldpop[i].chrom);
                //cout << tmpvolume << endl;
                if((tmpweight<=contain_weight) && (tmpvolume<=contain_volume)) {
                    cout << "find corret one" << endl;
                    cout << tmpvolume << endl;
                    cout << tmpweight << endl;
                    oldpop[i].fitness=cal_fit(oldpop[i].chrom);
                    oldpop[i].weight=tmpweight;
                    oldpop[i].volume=tmpvolume;
                    oldpop[i].parent1=0;
                    oldpop[i].parent2=0;
                    oldpop[i].cross=0;
                    ispop=true;
                }
            }
            ispop=false;
        }
    }

    //选择
    int selection(int pop) {
        double wheel_pos,rand_number,partsum;
        int parent;
        //赌轮法
        rand_number=(rand()%2001)/2000.0;
        wheel_pos=rand_number*sumfitness;
        partsum=0;
        parent=0;
        do{
            partsum=partsum+oldpop[parent].fitness;
            parent=parent+1;
        }while(partsum<wheel_pos&&parent<popsize);
        return parent-1;
    }

    //概率选择试验
    int execise(double probability) {
        double pp;
        pp=(double)((rand()%20001)/20000.0);
        if(pp<probability) return 1;
        return 0;
    }

    //交叉
    int crossover(unsigned int *parent1,unsigned int *parent2,int i) {
        int j,cross_pos;
        if(execise(pc)) {
            cross_pos=rand()%(lchrom-1);
        }
        else cross_pos=lchrom-1;
        for(j=0;j<=cross_pos;j++) {
            newpop[i].chrom[j]=parent1[j];
        }
        for(j=cross_pos+1;j<lchrom;j++) {
            newpop[i].chrom[j]=parent2[j];
        }
        newpop[i].cross=cross_pos;
        return 1;
    }

    //变异
    int mutation(unsigned int alleles) {
        if(execise(pm)) {
            if(alleles)
                alleles=0;
            else alleles=1;
        }
        return alleles;
    }

    //群体更新
    void generation() {
        unsigned int i,j,mate1,mate2;
        double tmpweight,tmpvolume;
        int ispop;
        i=0;
        while(i<popsize) {
            ispop=false;
            while(!ispop) {
                //选择
                mate1=selection(i);
                mate2=selection(i+1);
                //交叉
                crossover(oldpop[mate1].chrom,oldpop[mate2].chrom,i);
                //变异
                for(j=0;j<lchrom;j++) {
                    newpop[i].chrom[j]=mutation(newpop[i].chrom[j]);
                }
                //选择重量小于背包容量的个体
                tmpweight=cal_weight(newpop[i].chrom);
                tmpvolume=cal_volume(newpop[i].chrom);
                if((tmpweight<=contain_weight) && (tmpvolume<=contain_volume)) {
                    newpop[i].fitness=cal_fit(newpop[i].chrom);
                    newpop[i].weight=tmpweight;
                    newpop[i].volume=tmpvolume;
                    newpop[i].parent1=mate1;
                    newpop[i].parent2=mate2;
                    ispop=true;
                }
            }
            i=i+1;
        }
    }

public:

    void work() {            // 工作函数，用于计算结果
        int gen = 0,oldmaxpop,k,randpos;
        double oldmax;
        gen=0;
        srand((unsigned)time(NULL));

        initpop();          // 初始化种群
        for(int k=0; k<popsize; k++)
            newpop[k]=oldpop[k];

        statistics(newpop);  // 统计
        report(newpop,gen);  // 报告
        while(gen<maxgen) {
            gen=gen+1;
            if(gen%100==0)
                srand((unsigned)time(NULL));
            oldmax=curmaxfitness;
            oldmaxpop=maxpop;
            generation();              // 更新
            statistics(newpop);        // 统计
            if(curmaxfitness<oldmax)
            {
                randpos=rand()%popsize;
                for(k=0;k<lchrom;k++)
                    newpop[randpos].chrom[k]=oldpop[oldmaxpop].chrom[k];
                newpop[randpos].fitness=oldpop[oldmaxpop].fitness ;
                newpop[randpos].weight=oldpop[oldmaxpop].weight ;
                newpop[randpos].parent1 =oldpop[oldmaxpop].parent1 ;
                newpop[randpos].parent2 =oldpop[oldmaxpop].parent2;
                newpop[randpos].cross =oldpop[oldmaxpop].cross;
                statistics(newpop);
            }
            else if(curmaxfitness>oldmax)
            {
                report(newpop,gen);
            }
            for(k=0;k<popsize;k++)
                oldpop[k]=newpop[k];
        }

        cout<<endl<<"It's over!"<<endl;

        if (newpop[maxpop].fitness != 97)
        {
            cout << "the result should be 97" << endl;
            cout << "bad luck, please try again!" << endl;
        }
        system("pause");
    }

};

int main()
{

    cout << "hello" << endl;

     //背包问题中物体重量、价值、背包容量
    int weight[lchrom] = {22,15, 4, 5,10,19,21,20, 8,13, 2, 3, 3,17,12, 5,12, 4, 1,21,14,23,17,15,20,22,25, 0,22,15,25,13};
    int volume[lchrom] = {11,22,12,21,21,13, 1,10,13, 8, 6,25,13,27,12,23,12,24,23,11, 6,24,28,10,20,13,25,23, 5,26,30,15};
    int profit[lchrom] = { 8, 9,15, 6,16, 9, 1, 4,14, 9, 3, 7,12, 4,15, 5,18, 5,15, 4, 6, 2,12,14,11, 9,13,13,14,13,19, 4};
    int contain_weight = 80;
    int contain_volume = 75;

    CGeneAlgoOperater CTest(contain_weight, contain_volume, weight, volume, profit); // 传入数据
    CTest.work(); // 执行算法，输出结果

    return 0;
}



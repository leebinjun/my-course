import pandas as pd
import datetime
import matplotlib
from matplotlib import pyplot as plt
import seaborn
import numpy as np
matplotlib.rcParams['figure.figsize'] = (16, 5)
#%% 时间度量
global day_delay
day_delay=3
#%% 数据读取
user_df=pd.read_csv('../../data/dutir_tianchi_mobile_recommend/tianchi_mobile_recommend_train_user.csv')
item_df=pd.read_csv('../../data/dutir_tianchi_mobile_recommend/tianchi_mobile_recommend_train_item.csv')
#%% 简单统计
print('用户数量：',user_df.user_id.unique().shape[0])
print('商品总数量：',user_df.item_id.unique().shape[0])
print('操作记录总数：',len(user_df))
print('要预测的商品总数量:',item_df.item_id.unique().shape[0])
#%% 只预测这个set中出现的商品
item_id_set=set(item_df.item_id)
#%% 将时间变换一下
user_df['day']=user_df.time.apply(lambda x:datetime.datetime.strptime(x[:-3], "%Y-%m-%d"))
user_df['hour']=user_df.time.apply(lambda x:int(x[-2:]))
#%% 统计
print('每种行为的数量')
pd.DataFrame(user_df.behavior_type.value_counts())
print('每天的行为数量')
pd.DataFrame(user_df.day.value_counts()).plot()
#%%
item_cate=user_df.loc[:,['item_id','item_category']].drop_duplicates('item_id')
item_cate=pd.DataFrame(list(item_cate.item_category),index=list(item_cate.item_id))
#%% 提取出17号的加入购物车（3）的用户商品对
def submit(result_df,filename='../data/submission.csv'):
    result_df=result_df.loc[:,['user_id','item_id']].drop_duplicates()
    print('结果共有：',len(result_df),'条数据')
    result_df.to_csv(filename,index=False)
result_df=user_df[(user_df.day=='2014-12-17')&(user_df.behavior_type==3)]
# 筛选出要预测的商品，因为我们只评估这部分商品
result_df=result_df[result_df.item_id.apply(lambda id:id in item_id_set)]
submit(result_df,'../../data/submission1.csv')
#%% 发现每天购买o2o商品的平均用户商品对数量为400
o2o_user_df=user_df[user_df.item_id.apply(lambda id:id in item_id_set)]
buy_cnt=o2o_user_df[o2o_user_df.behavior_type==4].drop_duplicates(subset=['user_id','item_id','day']).day.value_counts()
pd.DataFrame(buy_cnt).plot()
plt.title('Buy Count Per Day')
#%% 17号最晚的收藏的前400个用户商品对
result_df=result_df.sort_values('hour',ascending=False).loc[:,['user_id','item_id']].drop_duplicates()
result_df=result_df.iloc[:400]
submit(result_df,'../../data/submission2.csv')

#%% 提取14号之后的数据
d=datetime.datetime(2014,12,17)-datetime.timedelta(day_delay)
 
o2o_user_df=o2o_user_df[o2o_user_df.day>=d]
print('数据个数：',len(user_df))
print('与要预测商品相关的数据个数',len(o2o_user_df))
#%%
def get_answer_dict(date):
    answer = user_df[(user_df.day==date)&(user_df.behavior_type==4)]
    answer = set(answer.apply(lambda item:'%s-%s'%(item.user_id,item.item_id),axis=1))
    return answer

def label_it(train_xs_df,target_date):
    answer=get_answer_dict(target_date)
    train_xs_df['label']=train_xs_df.apply(lambda item:1 if '%d-%d'%(item.user_id,item.item_id) in answer else 0,axis=1)
    return train_xs_df

def get_features(target_date,user_df,item_cate):
    xs=[]
    cnt=0
    start_date=target_date-datetime.timedelta(day_delay-1)#使用前两天的数据
    tmp_df=user_df[(user_df.day>=start_date)&(user_df.day<target_date)]
    
    a=tmp_df.loc[:,['user_id','item_category','behavior_type']] 
    a['count']=1
    b=a.groupby(by=['user_id','item_category','behavior_type'])
    e=b.sum()                                            #user 与 商品分类的关系

    a=tmp_df.loc[:,['user_id','item_id','behavior_type']]    
    
    a['count']=1
    e1=a.groupby(by=['user_id','behavior_type']).sum()   #user 2天内的 行为统计
    e2=a.groupby(by=['item_id','behavior_type']).sum()   #item 2天内的 行为统计

    for gid,items in tmp_df.groupby(by=['user_id','item_id']):
        user_id,item_id=gid
        x=[user_id,item_id]
        vals=np.zeros([day_delay-1,3,4])
        for item in items.itertuples():
            day=(target_date-item.day).days-1
            hour=int(item.hour/8)
            behavior=item.behavior_type-1
            vals[day][hour][behavior]+=1
        x.extend(list(vals.reshape(((day_delay-1)*12))))
        
        h=vals.sum(axis=1).sum(axis=0)
        x.extend(h)
        n0=h[0]#用户点击该商品总量
        
        h=e.loc[(user_id,item_cate.loc[item_id][0])]
        l=[0,0,0,0]
        for i in h.index:
            l[i-1]=np.log10(h.loc[i]['count']+1)
        x.extend(l)
        
        h=e1.loc[user_id]
        l=[0,0,0,0]
        for i in h.index:
            l[i-1]=np.log10(h.loc[i]['count']+1)
        x.extend(l)
        n1=10**l[0]#用户总点击量
        
        
        h=e2.loc[item_id]
        l=[0,0,0,0]
        for i in h.index:
            l[i-1]=np.log10(h.loc[i]['count']+1)
        x.extend(l)
        n2=10**l[0]#商品总点击量
        x.extend([n0/n1,n0/n2])
        
        xs.append(x)
        cnt+=1
        if cnt%10000==0:
            print(datetime.datetime.now(),'processed %d'%(cnt,))
        
    headers=['user_id','item_id']
    for i in range(day_delay-1):
        for j in range(3):
            for k in range(4):
                headers.append('d%d_h%d_b%d'%(i+1,j+1,k+1))
    headers.append('ui1')
    headers.append('ui2')
    headers.append('ui3')
    headers.append('ui4')
    headers.append('c1')
    headers.append('c2')
    headers.append('c3')
    headers.append('c4')
    headers.append('u1')
    headers.append('u2')
    headers.append('u3')
    headers.append('u4')
    headers.append('i1')
    headers.append('i2')
    headers.append('i3')
    headers.append('i4')
    headers.append('u/t')
    headers.append('i/t')
    xs_df=pd.DataFrame(xs,columns=headers)
    return xs_df
#%%
train_xs_df=get_features(datetime.datetime(2014,12,16),user_df,item_cate)
print(datetime.datetime.now(),'train_xs_df processed')
# 验证集和测试集只使用o2o的商品就可以了
valid_xs_df=get_features(datetime.datetime(2014,12,17),o2o_user_df,item_cate)
print(datetime.datetime.now(),'valid_xs_df processed')
test_xs_df=get_features(datetime.datetime(2014,12,18), o2o_user_df,item_cate)
print(datetime.datetime.now(),'test_xs_df processed')
#%%
label_it(train_xs_df,datetime.datetime(2014,12,16))
label_it(valid_xs_df,datetime.datetime(2014,12,17))
#%%
positive_num=np.sum(train_xs_df.label)
negative_num=len(train_xs_df)-positive_num
print('正样本个数',positive_num,'负样本个数',negative_num,'负正样本比例',negative_num/positive_num)
#%%
positive_xs_df=train_xs_df[train_xs_df.label==1]
positive_xs_df=positive_xs_df.sample(n=40000,replace=True)
sample_xs_df=pd.concat([train_xs_df,positive_xs_df])
sample_xs_df=sample_xs_df.sample(frac=1.0)
#%%
from sklearn.linear_model.logistic import LogisticRegression
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import Normalizer
from sklearn.metrics import precision_recall_fscore_support,precision_score,recall_score,f1_score
#%%
scaler=Normalizer(norm='l1')
scaler.fit(sample_xs_df.drop(['user_id','item_id','label']))
#%%
train_xs0=scaler.transform(sample_xs_df.drop(['user_id','item_id','label'],axis=1))
valid_xs0=scaler.transform(valid_xs_df.drop(['user_id','item_id','label'],axis=1))
test_xs0=scaler.transform(test_xs_df.drop(['user_id','item_id'],axis=1))
#%%
answer_cnt=len(o2o_user_df[(o2o_user_df.day=='2014-12-17')&(o2o_user_df.behavior_type==4)])
def evaluate(ytrue,ypred,answer_cnt):
    ypred=ypred>0.5
    right_cnt=np.sum(ytrue&ypred)
    predict_cnt=np.sum(ypred)
    precision=right_cnt/predict_cnt
    recall=right_cnt/answer_cnt
    f1=0
    if precision>0 or recall>0:
        f1=2*precision*recall/(precision+recall)
    print('预测数量',predict_cnt,'答案数量',answer_cnt)
    print('正确个数',right_cnt)
    print('precision',precision)
    print('recall',recall)
    print('f1',f1)
    return precision,recall,f1
#%%
from sklearn.feature_selection import RFE

rfe = RFE(LogisticRegression(C=10), 30) 
fit = rfe.fit(train_xs0[:,:-2],sample_xs_df.label)
#%%
feature=[]
names=train_xs_df.columns.values[2:] 
for i in range(len(fit.support_)):
    if fit.support_[i]:
        feature.append(i)
        print(names[i])
#%%
train_xs=train_xs0[:,feature]
valid_xs=valid_xs0[:,feature]
test_xs=test_xs0[:,feature]
#%%
#%%
clf1=LogisticRegression(C=10)
#训练模型
clf1.fit(train_xs,sample_xs_df.label)
#输出验证集结果
train_yp1=clf1.predict(train_xs)
valid_yp1=clf1.predict(valid_xs)
#输出测试集结果
test_yp1=clf1.predict(test_xs)
#结果线下评估
evaluate(valid_xs_df.label,valid_yp1,answer_cnt)
##测试集结果提交到文件中
#test_xs_df['yp']=test_yp1
#submit(test_xs_df[test_xs_df.yp==1],filename='../../data/submission_lr.csv')
#%%
clf2=GradientBoostingClassifier(n_estimators=200)
clf2.fit(train_xs,sample_xs_df.label)
# 这里可以用predict也可以用predict_proba
# predict只输出0和1，
# predict_proba 可以输出概率值
train_yp2=clf2.predict_proba(train_xs)[:,1]
valid_yp2=clf2.predict_proba(valid_xs)[:,1]
test_yp2=clf2.predict_proba(test_xs)[:,1]
evaluate(valid_xs_df.label,valid_yp2,answer_cnt)
test_xs_df['yp']=test_yp2
submit(test_xs_df[test_xs_df.yp>0.5],filename='../../data/submission_gbdt.csv')
#%%
clf3=RandomForestClassifier(n_estimators=200,n_jobs=4)
clf3.fit(train_xs,sample_xs_df.label)
# 这里可以用predict也可以用predict_proba
# predict只输出0和1，
# predict_proba 可以输出概率值
train_yp3=clf3.predict_proba(train_xs)[:,1]
valid_yp3=clf3.predict_proba(valid_xs)[:,1]
test_yp3=clf3.predict_proba(test_xs)[:,1]
evaluate(valid_xs_df.label,valid_yp3,answer_cnt)
#test_xs_df['yp']=test_yp
#submit(test_xs_df[test_xs_df.yp>0.5],filename='../../data/submission_rf.csv')
#%%
from sklearn.svm import SVC
clf4 = SVC(max_iter=1000)  
clf4.fit(train_xs,sample_xs_df.label)
train_yp4=clf4.predict(train_xs)
valid_yp4=clf4.predict(valid_xs)
evaluate(valid_xs_df.label,valid_yp4,answer_cnt)
#%%
from sklearn.neighbors import KNeighborsClassifier
clf=KNeighborsClassifier()
clf.fit(train_xs,sample_xs_df.label)
valid_yp5=clf.predict(valid_xs)
evaluate(valid_xs_df.label,valid_yp5,answer_cnt)
#%%
from sklearn.naive_bayes import GaussianNB
clf5=GaussianNB()
clf5.fit(train_xs,sample_xs_df.label)
train_yp5=clf5.predict(train_xs)
valid_yp5=clf5.predict(valid_xs)
evaluate(valid_xs_df.label,valid_yp5,answer_cnt)
#%%
from xgboost import XGBClassifier
xgbc=XGBClassifier(n_estimators=500,n_jobs=4)
xgbc.fit(train_xs,sample_xs_df.label)

valid_yp6=xgbc.predict(valid_xs)
test_yp6=xgbc.predict(test_xs)
evaluate(valid_xs_df.label,valid_yp6,answer_cnt)
test_xs_df['yp']=test_yp6
submit(test_xs_df[test_xs_df.yp>0.5],filename='../../data/submission_xgbst.csv')
#%%
#train_yp_total=[]
#valid_yp_total=[]
#for i in range(len(train_yp1)):
#    train_yp_total.append([train_yp1[i],train_yp2[i],train_yp6[i]])
#train_yp_total=np.array(train_yp_total)
#for i in range(len(valid_yp1)):
#    valid_yp_total.append([valid_yp1[i],train_yp2[i],valid_yp6[i]])
#valid_yp_total=np.array(valid_yp_total)   
#%%
test_yp_total=[]
for i in range(len(test_yp1)):
    test_yp_total.append([test_yp1[i],test_yp2[i]>0.5,test_yp6[i]])
test_yp_total=np.array(test_yp_total)   
test_yp_total=test_yp_total.sum(axis=1)>=2
test_xs_df['yp']=test_yp_total
submit(test_xs_df[test_xs_df.yp>0.5],filename='../../data/submission_fuse.csv')
##%%
#clf7=GradientBoostingClassifier()
#clf7.fit(train_yp_total,sample_xs_df.label)
#valid_yp7=clf7.predict(valid_yp_total)
#evaluate(valid_xs_df.label,valid_yp7,answer_cnt)
#evaluate(valid_xs_df.label,valid_yp_total.sum(axis=1)>=1,answer_cnt)
##%%
def fuse(train_yp_total,sample_xs_df,valid_yp_total,valid_xs_df):
    s_train=train_yp_total.sum(axis=1)
    nozid=np.where(s_train!=0)
    noz_train=train_yp_total[nozid]
    noz_train_label=np.array(sample_xs_df.label)[nozid]
    clf8=LogisticRegression()
    clf8.fit(noz_train,noz_train_label)
    
    valid_yp8=np.zeros([len(np.array(valid_xs_df))])
    nozid=np.where(valid_yp_total.sum(axis=1)!=0)
    noz_valid=valid_yp_total[nozid]
    noz_valid_yp8=clf8.predict(noz_valid)
    valid_yp8[nozid]=noz_valid_yp8
    evaluate(valid_xs_df.label,valid_yp8,answer_cnt)
#fuse(train_yp_total,sample_xs_df,valid_yp_total,valid_xs_df)
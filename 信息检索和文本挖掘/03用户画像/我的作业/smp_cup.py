# -*- coding: utf-8 -*-
#%%
import pandas as pd
import numpy as np
import random
import datetime
#%%
provsString='''
    东北,辽宁,吉林,黑龙江
    华北,河北,山西,内蒙古,北京,天津
    华东,山东,江苏,安徽,浙江,台湾,福建,江西,上海
    华中,河南,湖北,湖南
    华南,广东,广西,海南,香港,澳门
    西南,云南,重庆,贵州,四川,西藏
    西北,新疆,陕西,宁夏,青海,甘肃
    境外,其他,海外
    None,None
    '''
provs={}
for line in provsString.split('\n'):
    items=line.split(',')
    for item in items[1:]:
        provs[item]=items[0].strip()
#%%    
def map_age(x):
    x=int(x)
    if x>=1990:
        return '1990+'
    elif x<1980:
        return '1979-'
    else:
        return '1980-1989'
    
def map_location(x):
    x=x.split(' ')[0]
    return provs[x]

def changehour(x):
    if len(x)>15:
        return int(int(x[11:13])/4)
    elif len(x)==8:
        return int(int(x[3:5])/4)
    else:
        return -1

def total_accuray(A1,A2,A3):
    A=0.3*A1+0.2*A2+0.5*A3
    print('total:',A)
    return A

def accuracy(predict,real,string):
    l1=len(predict)
    l2=len(real)
    t=0
    if l1==l2:
        for i in range(l1):
            if predict[i]==real[i]:
                t+=1
        print(string+':',t/l1)
        return t/l1
    else:
        print('输入错误')
#%% 读取数据
#读取训练集
train_file=map(lambda x:x.split(',',maxsplit=5),open('train/train_status.txt',encoding='utf8'))
valid_labels=set(map(lambda x:x.strip(),open('valid/valid_nolabel.txt')))
valid_file=filter(lambda x:x[0] in valid_labels,map(lambda x:x.split(',',maxsplit=5),open('valid/valid_status.txt',encoding='utf8')))

df=pd.DataFrame(data=list(train_file)+list(valid_file),columns='id,review,forward,source,time,content'.split(','),)

#读取训练集标注
labels=pd.read_csv('train/train_labels.txt',sep='\|\|',encoding='utf8',engine='python',names='id,gender,age,location'.split(','))

labels.age=labels.age.apply(map_age)
labels.location=labels.location.apply(map_location)

#读取粉丝
fans={}
with open("train/train_links.txt") as f:
    for i in f:
        l=[int(i) for i in i.split()]
        fans[l[0]]=l[1:]
with open("valid/valid_links.txt") as f:
    for i in f:
        l=[int(i) for i in i.split()]
        fans[l[0]]=l[1:]
#%% 按id进行合并微博内容
X=pd.DataFrame(df.groupby(by='id',sort=False).content.sum()).reset_index()
X.id=X.id.astype(int)
data=pd.merge(X,labels,on='id',how='left')
#%% df数据化
df['id']=df.id.apply(lambda x:int(x))
df['review']=df.review.apply(lambda x:int(x))
df['forward']=df.forward.apply(lambda x:int(x))
df['hour']=df.time.apply(changehour)
df['isreview']=df['review']>0
df['vw_count']=1
#%% 统计
h=df.groupby(by='id').sum()
vw_amount=h['vw_count'].rename('vw_amount')#微博数
review_amount=h['review'].rename('review_amount')#回复数
isreview_amount=(h['isreview']/h['vw_count']).rename('r_review')#回复次数
forward_amount=h['forward'].rename('forward_amount')#转发数
#%% 朋友(互相关注)
friends={}
for i in fans.keys():
    friends[i]=[]
    l=fans[i]
    for j in l:
        if (j in fans) and (i in fans[j]):
            friends[i].append(j)
#%% 时间统计      
h=df.groupby(by='id').hour.value_counts()
t=np.zeros([len(data),6])
user=data['id'].unique()
for i in range(len(user)):
    l=h[user[i]]
    if -1 in l.index:
        l=l.drop(-1,axis=0)
    l=l/l.sum()
    for j in l.index:
        t[i][j]=l[j]
        
#%% data里面增加feature
for i in range(len(data)):
    l=data.iloc[i]
    id=l.id
    if id in fans:
        data.loc[i,'fans_amount']=len(fans[id])
        data.loc[i,'friends_amount']=len(friends[id])
    else:
        data.loc[i,'fans_amount']=0
        data.loc[i,'friends_amount']=0
data=pd.merge(data,pd.DataFrame(vw_amount),left_on='id',right_index=True)
data=pd.merge(data,pd.DataFrame(review_amount),left_on='id',right_index=True)
data=pd.merge(data,pd.DataFrame(isreview_amount),left_on='id',right_index=True)
data=pd.merge(data,pd.DataFrame(forward_amount),left_on='id',right_index=True)
for i in range(t.shape[1]):
    data.loc[:,'t'+str(i)]=t[:,i]
#%% 文本TF
from sklearn.feature_extraction.text import TfidfVectorizer

tfidf=TfidfVectorizer(max_features=10000)
f_tfidf=tfidf.fit_transform(data.content)
#%% 数据分割
train_amount=int(3200*0.8)

index_list=list(range(3200))
random.shuffle(index_list)

train=data.iloc[index_list[:train_amount],:].reset_index()
test=data.iloc[index_list[train_amount:],:].reset_index()
valid=data.iloc[3200:,:].reset_index()
#%% 归一化
from sklearn.preprocessing import Normalizer
scaler=Normalizer(norm='l1')
scaler.fit(train.iloc[:,-12:])
train_feature=scaler.transform(train.iloc[:,-12:])
test_feature=scaler.transform(test.iloc[:,-12:])
valid_feature=scaler.transform(valid.iloc[:,-12:])

f_tfidf=f_tfidf.toarray()
train_feature0=np.concatenate((f_tfidf[index_list[:train_amount]],train_feature),axis=1)
test_feature0=np.concatenate((f_tfidf[index_list[train_amount:]],test_feature),axis=1)
valid_feature0=np.concatenate((f_tfidf[3200:],valid_feature),axis=1)
#%%
from sklearn.decomposition import PCA
pca=PCA(n_components=10000,copy=True, whiten=False)
feature=pca.fit_transform(np.concatenate((train_feature0,test_feature0,valid_feature0),axis=0))
train_feature=feature[:train_amount]
test_feature=feature[train_amount:3200]
valid_feature=feature[3200:]
#%% 逻辑回归
from sklearn.linear_model.logistic import LogisticRegression as LR
valid_data1=valid

clf=LR(C=30)
clf.fit(train_feature,train.gender)
p_gender=clf.predict(test_feature)
a1=accuracy(p_gender,test.gender,'gender')
valid_data1.gender=clf.predict(valid_feature)

clf=LR(C=0.5)
clf.fit(train_feature,train.age)
p_age=clf.predict(test_feature)
a2=accuracy(p_age,test.age,'age')
valid_data1.age=clf.predict(valid_feature)

clf=LR(C=30)
clf.fit(train_feature,train.location)
p_location=clf.predict(test_feature)
a3=accuracy(p_location,test.location,'location')
A=total_accuray(a1,a2,a3)
valid_data1.location=clf.predict(valid_feature)
valid_data1.loc[:,['id','age','gender','location']].to_csv('LR.csv',index=False,encoding='utf-8')
#%% XGBoost
#from xgboost import XGBClassifier as xgbst
#valid_data2=valid
#
#clf=xgbst(n_jobs=4)
#clf.fit(train_feature,train.gender)
#p_gender=clf.predict(test_feature)
#a1=accuracy(p_gender,test.gender,'gender')
#valid_data1.gender=clf.predict(valid_feature)
#
#clf=xgbst(n_jobs=4)
#clf.fit(train_feature,train.age)
#p_age=clf.predict(test_feature)
#a2=accuracy(p_age,test.age,'age')
#valid_data1.age=clf.predict(valid_feature)
#
#clf=xgbst(n_jobs=4)
#clf.fit(train_feature,train.location)
#p_location=clf.predict(test_feature)
#a3=accuracy(p_location,test.location,'location')
#A=total_accuray(a1,a2,a3)
#valid_data2.location=clf.predict(valid_feature)
#valid_data2.loc[:,['id','age','gender','location']].to_csv('XGBoost.csv',index=False,encoding='utf-8')

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
        provs[item]=items[0].strip()#得到的provs()是一个字典，使得provs[各省]=地区，比如provs[辽宁]=东北;

def map_age(x):#年龄到年龄段的映射函数;
    x=int(x)
    if x>=1990:
        return '1990+'
    elif x<1980:
        return '1979-'
    else:
        return '1980-1989'
    
def map_location(x):#使用provs()字典进行省到地区的映射函数;
    x=x.split(' ')[0]
    return provs[x]



#从文件中读取语料并整理，将同一个人发的微博连在一起
import pandas as pd
#读取训练集
train_file=map(lambda x:x.split(',',maxsplit=5),
               open('train/train_status.txt',encoding='utf8'))#使用逗号分隔，五次，读到的是一个迭代器，转化为list之后[[第一行文字]，[第二行文字]];
valid_labels=set(map(lambda x:x.strip(),open('valid/valid_nolabel.txt')))#得到的valid_labels是一个集合，其中每个元素是一个数字;
valid_file=filter(lambda x:x[0] in valid_labels,
                  map(lambda x:x.split(',',maxsplit=5),
                      open('valid/valid_status.txt',encoding='utf8')))#filter()筛选函数，筛选x[0] in valid_labels的status条目;
df=pd.DataFrame(data=list(train_file)+list(valid_file), #这里把训练集合验证集进行了合并，前3200行是训练集，后1240行是验证集;
                columns='id,review,forward,source,time,content'.split(','),)#列标签，表格元素



#读取训练集标注
labels=pd.read_csv('train/train_labels.txt',sep='\|\|',encoding='utf8',engine='python',
                   names='id,gender,age,location'.split(','))

labels.age=labels.age.apply(map_age)
labels.location=labels.location.apply(map_location)
#按id进行合并微博内容
X=pd.DataFrame(df.groupby(by='id',sort=False).content.sum()).reset_index()
X.id=X.id.astype(int) 

data=pd.merge(X,labels,on='id',how='left')#这里得到的data每一行表示一个用户，分别包含 id 所发的微博所有内容 gender age location



#从文本中抽取TFIDF特征
from sklearn.feature_extraction.text import TfidfVectorizer

tfidf=TfidfVectorizer(max_features=10000)
f_tfidf=tfidf.fit_transform(data.content)#得到的是一个稀疏矩阵，第i行第j列，表示第i个样本的第j个词出现的TF-IDF频率

#训练逻辑回归分类器，并进行预测
#from sklearn.linear_model.logistic import LogisticRegression as LR
from sklearn import svm

valid_data=data[3200:].reset_index()#从data中取出验证集

clf=svm.SVC()
clf.fit(f_tfidf[:3200],data.gender[:3200])
valid_data.gender=clf.predict(f_tfidf[3200:])

clf=svm.SVC()
clf.fit(f_tfidf[:3200],data.age[:3200])
valid_data.age=clf.predict(f_tfidf[3200:])

clf=svm.SVC()
clf.fit(f_tfidf[:3200],data.location[:3200])
valid_data.location=clf.predict(f_tfidf[3200:])



#输出到temp.csv
valid_data.loc[:,['id','age','gender','location']].to_csv('temp.csv',index=False)
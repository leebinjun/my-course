#coding=utf-8
import sys
from collections import deque
import urllib3
from urllib import request
import re
from bs4 import BeautifulSoup
import lxml
import sqlite3
import jieba

safelock=input('你确定要重新构建约5000篇文档的词库吗？(y/n)')
if safelock!='y':
	sys.exit('终止。')

url='http://www.dlut.edu.cn/'#入口

queue=deque()#待爬取链接的集合，使用广度优先搜索
visited=set()#已访问的链接集合
queue.append(url)

conn=sqlite3.connect('viewsdu.db')
c=conn.cursor()
c.execute('drop table doc')
c.execute('create table doc (id int primary key,link text)')
c.execute('drop table word')
c.execute('create table word (term varchar(25) primary key,list text)')
conn.commit()
conn.close()

print('***************开始！***************************************************')
cnt=0

while queue:
    url=queue.popleft()
    visited.add(url)
    cnt+=1
    print('开始抓取第',cnt,'个链接：',url)

    #爬取网页内容
    try:
        response=request.urlopen(url)
        content=response.read().decode('utf-8')
        print("hello")
    except:
        print("hi")
        continue

    #寻找下一个可爬的链接
    print(content)
    m=re.findall(r'<a href=\"http:\/\/([0-9a-zA-Z\_\/\.\%\?\=\-\&]+)\" target=\"_blank\">',content,re.I)
    #              <a href="http://shebei2011.dlut.edu.cn/" target="_blank">
    #m=re.findall(r'<a href=\"([0-9a-zA-Z\_\/\.\%\?\=\-\&]+)\" target=\"_blank\">',content,re.I)
    print(m)
    for x in m:
        if re.match(r'http.+',x):
            x='http://'+x
         #   if not re.match(r'http\:\/\/www\.dlut\.edu\.cn\/.+',x):
          #      continue
        elif re.match(r'\/index\/.+',x):
            x='http://www.dlut.edu.cn'+x
        #elif re.match(r'')
        else:
            #x='http://www.dlut.edu.cn/'+x
            x='http://'+x
        if (x not in visited) and (x not in queue):
            queue.append(x)

	#解析网页内容,可能有几种情况
    soup=BeautifulSoup(content,'lxml')
    title=soup.title
    article=soup.find('div',class_='text_s',id='content')
    author=soup.find('div',class_='text_c')

    if title==None and article==None and author==None:
        print('无内容的页面。')
        continue

    elif article==None and author==None:
        print('只有标题。')
        title=title.text
        title=''.join(title.split())
        article=''
        author=''

	# elif title==None and author==None:
	# 	print('只有内容。')
	# 	title=''
	# 	article=article.get_text("",strip=True)
	# 	article=' '.join(article.split())
	# 	author=''

	# elif title==None and article==None:
	# 	print('只有作者。')
	# 	title=''
	# 	article=''
	# 	author=author.find_next_sibling('div',class_='text_c').get_text("",strip=True)
	# 	author=' '.join(author.split())

	# elif title==None:
	# 	print('有内容有作者，缺失标题')
	# 	title=''
	# 	article=article.get_text("",strip=True)
	# 	article=' '.join(article.split())
	# 	author=author.find_next_sibling('div',class_='text_c').get_text("",strip=True)
	# 	author=' '.join(author.split())

    elif article==None:
        print('有标题有作者，缺失内容')#视频新闻
        title=soup.h1.text
        title=''.join(title.split())
        article=''
        author=author.get_text("",strip=True)
        author=''.join(author.split())

    elif author==None:
        print('有标题有内容，缺失作者')
        title=soup.h1.text
        title=''.join(title.split())
        article=article.get_text("",strip=True)
        article=''.join(article.split())
        author=''

    else:
        title=soup.h1.text
        title=''.join(title.split())
        article=article.get_text("",strip=True)
        article=''.join(article.split())
        author=author.find_next_sibling('div',class_='text_c').get_text("",strip=True)
        author=''.join(author.split())
	
    print('网页标题：',title)

    #对网页内容分词
    seggen=jieba.cut_for_search(title)
    seglist=list(seggen)
    seggen=jieba.cut_for_search(article)
    seglist+=list(seggen)
    seggen=jieba.cut_for_search(author)
    seglist+=list(seggen)

    #数据存储
    conn=sqlite3.connect("viewsdu.db")
    c=conn.cursor()
    c.execute('insert into doc values(?,?)',(cnt,url))

    #对每个词语建立词表
    for word in seglist:
        print(word)
        #检验看看这个词语是否已存在于数据库
        c.execute('select list from word where term=?',(word,))
        result=c.fetchall()
        #如果不存在
        if len(result)==0:
            docliststr=str(cnt)
            c.execute('insert into word values(?,?)',(word,docliststr))
        #如果已存在
        else:
            docliststr=result[0][0]#得到字符串
            docliststr+=' '+str(cnt)
            c.execute('update word set list=? where term=?',(docliststr,word))

    conn.commit()
    conn.close()
    print('词表建立完毕=======================================================')

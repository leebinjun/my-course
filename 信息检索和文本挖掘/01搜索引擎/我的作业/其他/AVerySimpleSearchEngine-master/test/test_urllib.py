# -*- coding: utf-8 -*-
"""
Created on Sat Dec 16 11:50:55 2017

@author: Administrator
"""

from urllib import request
response=request.urlopen('http://www.dlut.edu.cn')
content=response.read().decode('utf-8')
print(content)#将会print整个网页的html源码
# -*- coding: utf-8 -*-
import search_engine_use as searchWD
from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

#装饰器
@app.route('/')
def index():
    #return render_template('test1.html', name = "chang")
    
    content = "{ url: http://xkb.dlut.edu.cn/info/1015/1002.htm , title: 大连理工大学有授予博士、硕士及专业学位的学科名单-大连理工大学学科建设办公室 ; url: http://news.dlut.edu.cn/info/1002/50799.htm , title: 大连理工大学彭孝军教授当选中国科学院院士-大连理工新闻网 ; url: http://news.dlut.edu.cn/info/1002/50779.htm , title: 大连理工大学孔宪京教授当选中国工程院院士-大连理工新闻网 ; url: http://jjw.dlut.edu.cn , title: 中共大连理工大学纪律检查委员会 大连理工大学监察处 ; url: http://www.dlut.edu.cn/ , title: 大连理工大学 ; url: http://en.dlut.edu.cn , title: Dalian University of Technology (DUT)|大连理工大学英文网站 ; }"
    return render_template('test1.html', name="binjun", content = content)
    #return "hello world!"

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8000, debug=True)

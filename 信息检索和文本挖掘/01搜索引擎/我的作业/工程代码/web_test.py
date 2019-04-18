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
    return render_template('index.html')
    #return "hello world!"

@app.route('/s')
def search():
    #return "hi!"
    if request.method == 'GET':
        wd = request.args.get('wd')
        print(wd)
        contentUrl,contentTit = searchWD.getWD(wd)
        #return "ok"
        #return(content)
        #return render_template('test1.html')
        #user = { content[]: content } # fake user
        print(contentUrl)
        print(contentTit)
        #return "ok"
        #return render_template('test2.html', contentUrl = contentUrl)
        #return render_template('test1.html', contentTit = contentTit, contentUrl =contentUrl)
        return render_template('index.html', t1 = contentTit[0],  t2 = contentTit[1], t3 = contentTit[2],  t4 = contentTit[3],  t5 = contentTit[4],
      u1 = contentUrl[0], u2 = contentUrl[1], u3 = contentUrl[2], u4 = contentUrl[3], u5 = contentUrl[4])
    else:
        return None

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8000, debug=True)

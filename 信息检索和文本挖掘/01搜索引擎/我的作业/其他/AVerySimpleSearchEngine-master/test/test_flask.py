# -*- coding: utf-8 -*-
"""
Created on Sun Dec 17 00:05:30 2017

@author: Administrator
"""

from flask import Flask
app = Flask(__name__)
@app.route("/")

def hello():
    return "Hello World!"

if __name__ == "__main__":
    app.run()

# -*- coding: utf-8 -*-
"""
Created on Sat Dec 16 12:33:14 2017

@author: Administrator
"""

import re
#re.match返回一个Match对象
if re.match(r'href=\".*view\.sdu\.edu\.cn.*\"','href="http://www.view.sdu.edu.cn/new/"'):
    print('ok')
else:
    print('failed')
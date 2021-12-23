

import json
from bs4 import BeautifulSoup
from bs4.element import PageElement, ResultSet, SoupStrainer
import requests
from requests.api import get, head
from requests.models import Response
import re
import pandas as pd
import psutil

class MyRandom:
    def __init__(self):
        # 代理ip
        self.proxy = {
        'http': 'http://219.141.153.41:80',
        #'https':'https://219.141.153.41:80'
        }
        #链接
        self.url='https://qt.gtimg.cn/?q=marketStat,sh000001,usDJI,r_hkHSI'
        #请求头
        self.headers={
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36',
        }

    
    '''获取随机数种子'''
    def get_seed(self):
        response = requests.get(url=self.url,headers=self.headers,proxies=self.proxy)
        response=re.findall(r"恒生指数~HSI~\d*\.\d*",response.text)
        response=re.sub(r"[^\d]","",response[0])
        return response
        

    '''产生num个[Min,Max]的随机数'''
    '''并保存到csv钟'''
    def Random(self,num,Min,Max):
        #两个大素数
        p=811
        q=719
        n=p*q
        s0=0
        mod = Max-Min+1
        #获取随机数种子
        while True:
            s0=int(self.get_seed())
            if s0%p!=0 and s0%q!=0 and s0%(n)!=0:
                break
        result=[]
        for i in range(num):
            s0=s0*s0%n
            s1=int(psutil.cpu_percent()*100)
            if s1==0:
              s1=1

            x=s0*s1%mod+Min

            result.append(x)

        dataframe=pd.DataFrame({'val':result})
        dataframe.to_csv("infosave/static/random_result.csv",index=True)



if __name__=='__main__':
    my_random=MyRandom()
    result=my_random.Random(1000,0,1000)

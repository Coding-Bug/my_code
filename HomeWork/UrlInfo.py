'''获取所有城市链接'''
# -*- coding: utf-8 -*-
from io import open_code
from os import PathLike, times
from bs4.element import SoupStrainer
import requests
from bs4 import BeautifulSoup
from requests.api import head
from requests.models import Response
import json
import re
import time
from urllib.parse import urljoin, urlparse

class UrlInfo:
  def __init__(self):
     # 代理ip
    self.proxy = {
    #'http': 'http://219.141.153.41:80',
    'https':'https://219.141.153.41:80'
    }
    #本地宝链接
    self.url='http://m.bendibao.com/city.php'
    #请求头
    self.headers={
      'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36',
    }



  '''获取所有城市的url保存到本地'''
  def get_all_page_url(self):
    page=requests.get(url=self.url,headers=self.headers)
    page.encoding='utf8'
    soup=BeautifulSoup(page.text,"html.parser")
    soup=soup.find_all("div",{"class":"col-xs-4 col-sm-3 col-md-2 col-lg-1"})
  
    city_sum_dest={} 
    for i in soup:
      i=i.find('a')
      city_sum_dest[i.string]=i['href'].strip("\n")
      
    # 写入文件
    with open("HomeWork/static/all_city_page_url.json",mode="wb") as f:
      f.write(json.dumps(city_sum_dest,ensure_ascii=False,indent=1).encode())
  


  '''拼接搜索链接'''
  def get_city_search_url(self,search):
    with open("HomeWork/static/all_city_page_url.json","r",encoding='utf-8') as f:
      city_sum_dest=json.load(f)
      f.close()
    
    query_url_dest={}
    
    for i in city_sum_dest:
      time.sleep(2)

      #请求
      try:
        page=requests.get(url=city_sum_dest[i],headers=self.headers,proxies=self.proxy)
      except:
        continue  

      soup=BeautifulSoup(page.text,"html.parser")
      query_url=soup.select(".search")
      query_url=str(query_url)

      # 用正则表达式获得href
      query_url=re.findall(r"<a.+?href=\"(.+?)\".*>",query_url)
      # 有的城市并没有搜索框，所以可能会找不到
      if query_url==[]:
        continue

      #拼接搜索
      query_url=str(query_url[0])
      query_url=urlparse(query_url)
      query_url=query_url.scheme+"://"+query_url.netloc+query_url.path+query_url.params+"?"+query_url.query+"&q="+i+search
      query_url_dest[i]=query_url

      
      #写入文件
      with open("HomeWork/static/all_city_search_url.json",mode="wb") as f:
        f.write(json.dumps(query_url_dest,ensure_ascii=False,indent=1).encode())


  '''获取详细页url'''
  def get_detail_page_url(self):
    #存放详细页的url
    detail_page_url={}

    #读取文件
    with open("HomeWork/static/all_city_search_url.json","r",encoding="utf8") as f:
      query_url_dest=json.load(f)
      f.close()

    for city in query_url_dest:
      time.sleep(2)

      #请求
      try:
        page=requests.get(url=query_url_dest[city],proxies=self.proxy,headers=self.headers)    
      except:
        continue
      
      page.encoding="utf8"
      soup=BeautifulSoup(page.text,"html.parser")
      soup=soup.find_all("a",{"cpos":"title"})
    
      #找第一个引进关键字的
      for j in soup:
        title = j.get_text()   # 该链接的标题
        if "引进" in title:
          detail_page_url[city+"人才引进"]=j["href"]
          break
      #找第一个补贴关键字的
      for j in soup:
        title = j.get_text()   # 该链接的标题
        if "补贴" in title:
          detail_page_url[city+"人才补贴"]=j["href"]
          break
      #找第一个落户关键字的
      for j in soup:
        title = j.get_text()   # 该链接的标题
        if "落户" in title:
          detail_page_url[city+"落户政策"]=j["href"]
          break
        
    # 储存到文件    
    with open("HomeWork/static/detail_page_url.json",mode="wb") as f:
      f.write(json.dumps(detail_page_url,ensure_ascii=False,indent=1).encode())



      
      

    

    


    








     
    



import json
from time import sleep
import requests
from bs4 import BeautifulSoup
import re
class PageInfo:
  def __init__(self) -> None:
    # 代理ip
    self.proxy = {
    #'http': 'http://219.141.153.41:80',
    'https':'https://219.141.153.41:80'
    }
    #请求头
    self.headers={
      'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36',
    }


  '''获取详细信息'''
  def get_page_detail(self,search):
    with open("HomeWork/static/detail_page_url.json","r",encoding='utf-8') as f:
      detail_page_url=json.load(f)
      f.close()
  
    url1=detail_page_url[search]
    try:
      page=requests.get(url=url1,proxies=self.proxy,headers=self.headers)
    except:
      print("页面不存在")
   
    page.encoding="utf8"
    soup=BeautifulSoup(page.text,"html.parser")
    soup=soup.find("div",{"class":"content","id":"bo"})
    info=""
    for i in soup:
      i=i.get_text().strip()
      info =info+i+'\n'
    info=re.sub(r"温馨提示.*\n*var.*\n*.*","",info)
    info=re.sub(r">","",info)
    
    print(info)
    with open("HomeWork/static/"+search+".txt","wb") as f:
      f.write(info.encode())
   


  

    

  
    


    
  



    

    

    
    

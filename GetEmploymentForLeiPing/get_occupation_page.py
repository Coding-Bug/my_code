
import requests
import re
from bs4 import BeautifulSoup
from requests.api import get
from requests.models import Response
class GetUrl:
  def __init__(self):

    # 代理ip
    self.proxy = {
    'http': 'http://219.141.153.41:80'
    }
    self.headers={
      'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36',
    }

    # 储存网址
    self.file = open('occupation_page.txt', 'wb')




  #得到所有招聘信息内容(非详细页)
  def get_response(self,html_url):
    try:
      response=requests.get(url=html_url,headers=self.headers,proxies=self.proxy)
      
    except Exception as e:
      print("爬取网页为空")

    return response

  #获取详细页的url
  def get_url(self,html_url):
    response=self.get_response(html_url=html_url)
    soup = BeautifulSoup(response.text, "html.parser")
    soup = soup.find_all(
        "a", {'data-nick': 'job-detail-job-info', 'target': '_blank'})  # 找到招聘详细信息的链接
    for i in soup:
      href=i['href']
      href=(href+"\n").encode()
      self.file.write(href)

   

if __name__=='__main__':
  g_url=GetUrl()
  for page in range(1,5):
    url=f'https://www.liepin.com/zhaopin/?key=前端&currentPage={page}'
    g_url.get_url(html_url=url)


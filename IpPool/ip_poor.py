import requests
import random
import time
from lxml import etree
from fake_useragent import UserAgent

class IpPool:
  def __init__(self):
    #测试ip是否可用url
    self.test_url = 'http://httpbin.org/get'
    # 获取IP的 目标url
    self.url = 'https://www.89ip.cn/index_{}.html'
    self.headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.94 Safari/537.36'}
    # 存储可用ip
    self.file = open('ip_pool.txt', 'wb')
 

  def get_html(self,url):
    #获取页面
    html=requests.get(url=url,headers=self.headers).text
    return html
  
  def get_proxy(self,url):
    #数据处理，获取ip和端口
    html = self.get_html(url=url)
    elemt = etree.HTML(html)
    ips_list = elemt.xpath('//table/tbody/tr/td[1]/text()')
    ports_list = elemt.xpath('//table/tbody/tr/td[2]/text()')
    for ip,port in zip(ips_list,ports_list):
      #拼接ip与port
      proxy=ip.strip()+":"+port.strip()

      self.test_proxy(proxy)


  def test_proxy(self,proxy):
    # 测试代理IP是否可用
    proxies={
      'http': 'http://{}'.format(proxy),
      'https': 'https://{}'.format(proxy),
    }

    try:
      resp=requests.get(url=self.test_url,proxies=proxies, headers=self.headers)
      if resp.status_code==200:
        print(proxy,'\033[31m可用\033[0m')
        #可以用的IP，写入文本便后续使用
        self.file.write("proxy")
      else:
        print(proxy,'不可用')
        

    except Exception as e:
      print(proxy,'不可用')
    
  
  def crawl(self):
    #执行函数
    for i in range(1,101):
      #拼接完整的url
      page_url=self.url.format(i)
      # 注意抓取控制频率
      time.sleep(random.randint(1,2))
      self.get_proxy(url=page_url)


    # 关闭文本
    self.file.close()

if __name__=='__main__':
  ip=IpPool()
  ip.crawl()

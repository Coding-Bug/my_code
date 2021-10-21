
# -*- coding: utf-8 -*-
from types import SimpleNamespace
import requests
from requests.models import Response
import datetime
from bs4 import BeautifulSoup
import re
import csv

class GetOccupationDetail:
  def __init__(self) -> None:
    # 代理ip
    self.proxy = {
    'http': 'http://219.141.153.41:80'
    }
    self.headers={
      'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36',
    }

  #获取整个页面
  def get_response(self,url):
    try:
      response=requests.get(url=url,headers=self.headers,proxies=self.proxy)
      
    except Exception as e:
      raise e

    return response
  
  #对数据进行整理
  def reduct_data(self,response):
    #爬取时间
    crawl_time = datetime.datetime.now()
    crawl_time = crawl_time.strftime(("%Y-%m-%d %H:%M:%S"))
    soup = BeautifulSoup(response.text, "html.parser")
    # 招聘岗位
    job_name=soup.find("span",{'class':'name ellipsis-1'}).get_text().strip()
    
    # 薪资
    salary=soup.find("span",{'class':'salary'}).get_text()
    #print(salary)

    # |址位地区|工作年限|职位实习/应届|
    job_properties=soup.find("div",{'class':'job-properties'}).contents
    #print(job_properties)

    job_city=job_properties[3].get_text().strip()
    #print(job_address)
    
    job_year=job_properties[9].get_text().strip()
    #print(job_year)
    
    job_education=job_properties[17].get_text().strip()
    #print(job_education)
    
    #公司名称       
    job_company=soup.find("div",{'class':'title-box'}).contents
    
    job_company=job_company[3].get_text().replace('·','')
    job_company=job_company.strip()
    
 

    # 岗位介绍
    job_intro=soup.find("dl",{'class':'paragraph'}).contents
    job_intro=job_intro[3].get_text().strip()
    #print(job_intro)

    result=[crawl_time,job_name,job_city,job_education,salary,job_year,job_company,job_intro]
    #print(result)
    
    return result
     

  # 保存数据到csv文件 
  def save_to_csv(self,results,work_direction):
    '''保存数据到csv'''
    
    headers=['crawl_time','job_name','job_city','job_education','salary','job_year','job_company']
    with open(work_direction+'招聘信息.csv','a',encoding='utf8', newline='') as f:
      f_csv=csv.writer(f)
      f_csv.writerow(headers)
      f_csv.writerows(results)
  
  # 公司介绍保存到txt
  def save_to_txt(self,result,work_direction):
    job_company=result[6]
    job_intro=result[7]
    with open(work_direction+"数据挖掘/"+job_company+".txt","wb",) as f:
      f.write(job_intro.encode())

  # 获取数据
  def get_detail(self,url):
    try:
      response=self.get_response(url=url)

    except Exception as e:
      print("爬取错误")

    #对数据进行整理和保存
    result=self.reduct_data(response=response)

    return result

   
    
if __name__ =="__main__":
  get_deatil=GetOccupationDetail()
  file_name='occupation_page.txt'
  results=[]
  work_direction='前端'
  with open(file_name) as urls:
     for url in urls:
       result=(get_deatil.get_detail(url=url))
       #将岗位职责等保存到txt文件
       get_deatil.save_to_txt(result=result,work_direction=work_direction)
       #将岗位职责删去
       result.pop()
       results.append(result)

  #生成csv文件
  get_deatil.save_to_csv(results=results,work_direction=work_direction)
    
  
  

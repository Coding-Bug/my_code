import requests
from bs4 import BeautifulSoup

# 获取招聘详情链接
def get_occupation_detail():


  url = "https://www.liepin.com/zhaopin/?key=数据挖掘&dqs=010"
  page = requests.get(url=url)
  soup = BeautifulSoup(page.text, "html.parser")
  soup = soup.find_all(
      "a", {'data-nick': 'job-detail-job-info', 'target': '_blank'})  # 找到招聘详细信息的链接
  return soup


if __name__=='__main__':
  result=get_occupation_detail()
  print(result)

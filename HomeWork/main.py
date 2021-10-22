from re import search
from typing import FrozenSet
from PageInfo import PageInfo
from UrlInfo import UrlInfo
from DateCleaner import DateCleaner


if __name__=='__main__':
  url_info=UrlInfo()  #创建爬取搜索链接的对象
  #info.get_all_page_url()
  #info.get_city_search_url(search="2021人才引进")
  #url_info.get_detail_page_url()

  page_info=PageInfo()  # 爬取详细页的对象
  # page_info.get_page_detail(search="武汉人才引进") 
  # page_info.get_page_detail(search="武汉人才补贴")
  # page_info.get_page_detail(search="武汉落户政策")
  date_cleaner=DateCleaner()
  date_cleaner.clean_intro_info(file="Homework/static/武汉人才引进.txt")



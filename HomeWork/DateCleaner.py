# -*- coding: utf-8 -*-

import re
class DateCleaner:

  '''清洗人才引进数据'''
  def clean_intro_info(self,file):
    list_num=0   #落户种类的数量
    with open(file,"r",encoding="utf8") as f:
      text=f.read()
    
    # 存放人才引进种类
    # intro_species=[]  
    # intro_species=re.findall(r"[一二三四五六七八九]、.*",text)
    # print(intro_species)

    # 存放人才引进申请条件
    apply_req=[]
    #temp1存放每种人才的全部申请条件
    temp1=re.findall(r'申请条件.*\n.*',text)
    #k是人才种类序号
    k=0
    for i in temp1:
      #temp2存放某种人才的全部申请条件
      temp2=re.sub(r'申请条件.*\n',"",i)
      temp2=re.findall(r'.*,?',temp2)
      for j in temp2:
        #temp3存放某种人才的某种申请条件
        temp3=re.sub(r"[\,\。]","",j)
        apply_req[k].append(temp3)
        
      print(apply_req[k])
      k=k+1



      
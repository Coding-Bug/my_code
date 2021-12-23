# -*- coding:utf-8 -*-
from os import rename
from matplotlib import colors, markers
from numpy import DataSource, arange, zeros
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
class Checkout:
    def __init__(self,num) -> None:
        self.data=pd.read_csv('infosave/static/random_result.csv')
        self.num=num  #数据量
        
    '''随机性检验'''
    def randomness(self):
        data=self.data['val']
        sum=np.zeros(1001)
        for i in data:
            sum[i]=sum[i]+1
        
        fre=[] # 出现频率
        for i in sum:
            fre.append(i/self.num)
        
        # 保存频率
        randomness_fre=pd.DataFrame({'fre':fre}) 
        randomness_fre.to_csv("infosave/static/randomness_fre.csv",index=False)
        # 保存数量
        randomness_count=pd.DataFrame({'count':sum})
        randomness_count.to_csv("infosave/static/randomness_count.csv",index=False)
        
        # 将总数占比和频率画图
        x=np.arange(1001)
        plt.figure(figsize=(12,6),dpi=100)
        plt.rcParams['font.family'] = 'sans-serif'
        plt.rcParams['font.sans-serif'] = 'SimHei'
        plt.subplot(121)
        plt.xlabel('随机数值')
        plt.ylabel('随机数出现频率')
        plt.plot(x,fre,'m.')
        plt.subplot(122)
        plt.gca().yaxis.set_major_locator(MaxNLocator(integer=True))
        plt.xlabel('随机数值')
        plt.ylabel('随机数出现次数')
        plt.plot(x,sum,'m.')
        plt.show()
    


    
    '''进行周期性检验'''
    def periodism(self):
        data=self.data['val']
        x=np.arange(self.num)
        #将x和y分成五段
        my_y=[]
        my_x=[]
        my_x.append([])
        my_y.append([])
        k=0
        for i in range(self.num):
            my_y[k].append(data[i])
            my_x[k].append(x[i])
            if i!=0 and i%125==0:
                k=k+1
                my_x.append([])
                my_y.append([])
                

        
        for i in arange(8):
            plt.figure(figsize=(12,6),dpi=100)
            plt.rcParams['font.family'] = 'sans-serif'
            plt.rcParams['font.sans-serif'] = 'SimHei'
            plt.xlabel('随机数下标')
            plt.ylabel('随机数') 
            plt.plot(my_x[i], my_y[i],'m.')
        plt.show()



                      

if __name__=='__main__':
    my_checkout=Checkout(num=1000)
    #my_checkout.randomness()
    my_checkout.periodism()


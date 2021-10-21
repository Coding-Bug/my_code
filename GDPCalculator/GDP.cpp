#include<iostream>
int a;
using namespace std;

double GDP(double GDP[], int project_num ,double credit[]){
    double credit_sum = 0;          // 总学分
    double ans = 0;                 // 最终绩点
    // 计算总学分
    for(int i = 0;i<project_num;++i){
      credit_sum += credit[i];
    }
    for(int i = 0; i<project_num;++i){
        ans+= GDP[i]*(credit[i]/credit_sum);
    }
    return ans;
}
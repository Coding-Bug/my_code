#include<bits/stdc++.h>
using namespace std;
    int n,k;
    int w[10000]={0};
    int P = 0;    // 最大运载量
    long long  sum = 0;  // 当前车装的总重量
    

// 求最大载货量为P的时候能装的最多的货物量(注意用long long)
int load (long long P){
    int isLoaded = 0;   // 已经被装车货物的数量
    int isLoad = 1;     // 已经装的车数

    for (int i = 0; i < n; i++){

        // 如果这件商品已经超过了最大上限，则返回
        if(w[i] > P){
            return isLoaded;
        }

        // 如果当前车没满，就装
        if ( sum + w[i] < P){
            sum += w[i];
            isLoaded++;
        } else if (++isLoad <= k){  
            sum = w[i];
            isLoaded++;
        } else{
            return isLoaded;
        }
  
    }
    return isLoaded;
}

int main(){
    int a;
    cin >> n >> k;
    for (int i = 0; i < n; ++i){
        cin >> w[i];
    }
    /*
    这个算法设计有缺陷，首先，P不应该是10000，而应该是10000*100000
    其次，打么大的数据你枚举，要是最欢的情况就难搞了
    所以，这里的枚举应该改进一下，用二分法
    for (int P = 0; P< 10000; ++P){
        if (load(P) == n-1){
            cout << P << endl;
            system ("pause");
            return 0;
        }

    }
    */

   // 枚举的那部分算法应该这样写

   long long left = 0;
   long long right =100000 * 10000; // P的范围
   long long mid;
   while (right -left > 1){
       mid = (left + right) / 2;
       if ((a=load (mid)) < (n-1)){
          left = mid ;
       } else {       // 这里小细节，如果和n-1相等的话，我们找的是左半边，因为我们要找小的
           right = mid;
       }
   } 

   cout << left << endl;
   cout << right << endl;

    system ("pause");
    return 0;

    

   

}
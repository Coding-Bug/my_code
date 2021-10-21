#include<iostream>
#include<cmath>
#include<stdio.h>
using namespace std;
#define  PI 3.141593
int main()
{
    int  T;
    cin >> T;
    
    if(T == 1){
        cout << "I love Luogu!";}
    if(T==2){
        cout << 2+4 << " " << 10-2-4 << endl;
    }
    if (T==3){
        cout << 14/4 << endl;
        cout << 4 * (14 / 4) << endl;
        cout << 14 - 4*(14 / 4) << endl;
    }
    if (T == 4){
       cout << 166.667 << endl;
       }
    if (T == 5){
        int i = 0;
        while (1){
            if ((20 * i+ 12 * i) == 480 ){
                cout << i << endl;
                break;
            }
            ++i;
        }
    }
    if(T==6){
        cout << sqrt(117) << endl;
    }
    
    if(T==7){
        cout << 110 << endl;
        cout << 90 <<endl;
        cout << 0 << endl;
      }

    if(T==8){
        cout << 2 * 5 * PI << endl;
        cout << 5 * 5 * PI << endl;
        cout << (4.0 / 3) * PI * 125 << endl;
     }
    if(T==9){
        int ans = 1;
        for (int i = 4; i>1; --i){
            ans = ((ans + 1) * 2);
        }
        cout << ans << endl;
     }
    
    if(T==10){
        cout << 9 << endl;
    }
    
    if(T==11){
        cout << 100.0 / 3 << endl;
      }
    if(T==12){
        cout << int ('M' - 'A')+1 <<endl;
        cout << 'R' << endl;
     }
    if(T==13){
        double ans = 0;
        ans = pow( ((4.0/3)*PI*1064),1.0/3);
        cout << (int) ans << endl;
    }
    if(T==14){
        cout << 50 << endl; 
       }
system ("pause");
    return 0;
}
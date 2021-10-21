#include<iostream>
using namespace std;
 int main()
 {
     char ans;
     cin >> ans;
     if ( 'a' <= ans <= 'z'){
        cout << char (ans - 32) << endl;
     }
    else{
        cout << ans << endl; 
    }
    
    system ("pause");
    return 0;
    
 }
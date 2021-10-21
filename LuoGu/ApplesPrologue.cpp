#include<iostream>
using namespace std;
int main()
{
    int m, t, s;
    double a;
    int ans;
    cin >> m >> t >> s;
    if( t == 0){
        cout << 0 << endl;
        return 0;
    }
    a = (double) s / t;
    if( a == (int) a  )
          ans = m - a;
    else
    {
        ans =  m-(int)a-1;
    }
    
    if(ans >= 0 )
        cout << ans;
    else{
        cout << 0 << endl;
    }
    return 0;
}
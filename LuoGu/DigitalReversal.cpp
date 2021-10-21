#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    double m;
    cin >> m;
    int a = m * 10;
    int n = 0;
    double ans = 0;
    while ( a > 0 ){
        a = a / 10 ;
        ++n;
    }
    a = m * 10;

    for (int i = 0; i <= n; i++ ){
    
        ans += (a % 10) * pow (10, -i);
        a = a / 10;
    }

    cout << ans << endl;
    system ("pause");
    return 0;

}
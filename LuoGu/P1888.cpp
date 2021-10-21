#include<iostream>
using namespace std;

int gcd(int a, int b){
    if ((a % b) == 0){
        return b;
    }
    gcd (b,a % b);
}
int main()
{
    int a, b, c;
    int d;
    cin >> a >> b >> c;
    int mol = 0;    // 分子
    int den = 0;    // 分母
    den = a >(b > c? b:c)?a:(b > c? b:c);
    mol = a <(b < c? b:c)?a:(b < c? b:c);
    d = gcd(den , mol);
    mol /= d;
    den /= d;
    cout << mol << '/' << den << endl;
    return 0;

}
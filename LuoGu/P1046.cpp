#include<iostream>
using namespace std;
int main()
{
    int apple[10] = {0};
    int cap = 0;
    int ans = 0;
    for (int i = 0; i <10 ; ++i){
        cin >> apple [i];
    } 
    cin >> cap;
    for (int i = 0; i <10 ; ++i){
        if (apple[i] <= (cap + 30)){
            ans ++;
        }
    }
    cout << ans << endl;
    system ("pause");
    return 0;
}
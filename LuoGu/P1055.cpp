#include<iostream>
using namespace std;
int main()
{
    char in [14]={0};
    int sum = 0;
    int ans;
    char b = 0;
    cin >> in;
    int k = 1;
    for (int i = 0; i < 12; ++i){

        if(in[i] >= '0' && in[i] <= '9'){
            sum += k * (in[i] - 48);
            ++k;
        }
    }
    ans = sum % 11;
    if (ans == 10){
        b = 'X';
    }

    if(ans == (in[12] - 48) || in[12] == b){
        cout << "Right" << endl;
    } else{
        if( ans == 10){
            in[12] = 'X';
        } else {
        in[12] = ans + 48;
        }
        for(int j = 0; j < 14; j++){
            cout << in[j];
        }
    }

    return 0;

}
#include<iostream>
#include<stdio.h>
using namespace std;
int main(){
    double t = 0;
    int n = 0;
    cin >> t >> n;
    int cup = 2 * n;
    double coke = t / n;
    printf("%.3f\n" , coke);
    cout << cup << endl;
    return 0;

}
#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
int main()
{
   double a, b, c;
   cin >> a >> b >> c;
   double ans;
   double p;
   p = 0.5 * ( a + b + c );
   ans = sqrt( p * (p - a) *(p - b) * (p - c) );
   printf ("%.1f", ans);
   return 0;
}
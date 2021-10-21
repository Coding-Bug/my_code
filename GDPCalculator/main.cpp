#include <iostream>
using namespace std;
#include "GDP.cpp"
int main()
{
   freopen("must.txt", "r", stdin);
   double My_GDP[100];
   double My_Credit[100];
   int N = 0;

   while (cin >> My_GDP[N])
   {
      cin >> My_Credit[N++];
   }

   cout << "GDP";
   cout << GDP(My_GDP, N, My_Credit);
}
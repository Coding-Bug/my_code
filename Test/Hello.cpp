#include <iostream>
using namespace std;
int main()
{
    freopen("A.txt", "r", stdin);
    string str;
    cin >> str;
    for (int i = 1; i <= 26; ++i)
    {
        for (int j = 0; j < str.size(); ++j)
        {
            char c = char(str[j] - i);
            if (c < 'A')
            {
                c = 'Z' - (i - (str[j] - 'A' + 1));
            }
            cout << c;
        }
        cout << endl;
    }
}

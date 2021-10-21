#include <iostream>
#include <algorithm>
using namespace std;

// 字母结构体
typedef struct LETTER
{
  int c;     // 字母种类
  int count; // 次数
  double f;  // 对应频率
} LETTER;

bool cmp(LETTER a, LETTER b)
{
  if (a.count == b.count)
  {
    return a.c < b.c;
  }

  return a.count > b.count; // 出现次数大的在前面
}
LETTER let[27];   
string str;
int Sum = 0; //字符总数
int main()
{
  freopen("test/str.in", "r", stdin);
  freopen("test/b.out", "w", stdout);
  // 初始化
  for (int i = 0; i < 26; ++i)
  {
    let[i].c = i;
    let[i].count = 0;
    let[i].f = 0;
  }

  cin >> str;
  for (int i = 0; i < str.length(); ++i)
  {
    int temp = str[i] - 'A';
    let[temp].count++;
    Sum++;
  }

  sort(let, let + 26, cmp);
  for (int i = 0; i < 26; ++i)
  {
    let[i].f = (let[i].count * 1.0) / (Sum * 1.0);
    cout << "字母" << (char)(let[i].c + 'A') << "    频率：" << let[i].f << endl;
  }
}
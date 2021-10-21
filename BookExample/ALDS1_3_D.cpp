#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm> 
#include <utility>
using std::string;
using namespace std;
int main(){
    stack<int> S1;
    stack<pair<int, int> > S2;
    int sum = 0;
    string ch;
    cin >> ch;
    for(int i = 0; i < ch.size(); ++i ){
        if (ch[i] == '\\'){
           S1.push(i);
        }
        if ( ch[i] =='/' && S1.size() > 0 ) {
            int j = S1.top();
            S1.pop();
            sum += i - j;
            int a = i - j;
             while ( S2.size() > 0 && S2.top().first > j ) { // 在完成一块之后，这里就不符合条件了 
                a += S2.top().second; S2.pop();}             // 因为上面的j会变大（本来没完成一块积水之前，j是变小的，或者先变大再变小）
            S2.push(make_pair(j , a));                       // 然后就不会进入这里了，也就不会pop了，所以就算出了一小块的面积
        }
    }

    vector<int> ans;
    while (S2.size()>0)
    {
        ans.push_back(S2.top().second); 
        S2.pop();
    }

    // 因为我们要输出顺序是从栈的最里面输出的，所以要先取出来
    reverse(ans.begin(), ans.end());
    cout << sum << endl;
    cout << ans.size();
    for ( int i = 0; i < ans.size(); ++i){
        cout << " ";
        cout << ans[i];
    }
    cout << endl;
    system ("pause");
    return 0;
    

}
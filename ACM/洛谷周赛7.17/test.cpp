#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int T,n;
struct Node{
	int a,b,c,d;
	bool operator < (Node it)const
	{
		if(it.a==a)return it.b<b;
		else return it.a<a;
	}
};
struct node{
	int a,b,c,d;
	bool operator < (node it)const
	{
		return it.b<b;
	}
};
priority_queue <Node> q,p;//未装备，已装备，其实只是转移
priority_queue <node> r;//力量值足够穿

signed main(void)
{
    //freopen("test/A.txt","r",stdin);
	cin>>T>>n;
	if(!n)
	{
		cout<<"0 0\n";
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		int aa,bb,cc,dd;
		cin>>aa>>bb>>cc>>dd;
		q.push((Node){aa,bb,cc,dd});
	}

	int ini=0,now=0;
	while(!q.empty())
	{
		Node cur=q.top();
		q.pop();
		p.push(cur);
		if(now>=cur.a)//能够装备
		{
			now+=cur.c;
			continue;
		}

		else{//无法装备
			ini+=cur.a-now;
			now=cur.a;
			now+=cur.c;
		}
	}

	cout<<ini<<" ";
	now=ini;//求智慧值时要初始化力量值

	int init=0,nowt=0;

	while(!p.empty()||!r.empty())
	{
		int cnt=0;
		while(!p.empty()&&p.top().a<=now)//因为力量值会随着装备的增多而增大，所以需要维护r这个优先队列
		{
			cnt++;
			Node cur=p.top();
			r.push((node){cur.a,cur.b,cur.c,cur.d}),p.pop();
		}
		while(!r.empty()&&r.top().b<=nowt)//可以装备
		{
			node cur=r.top();r.pop();
			nowt+=cur.d;
			now+=cur.c;
		}
		if(cnt==0&&!r.empty())//无法装备，需要增加智慧值
		{
			node cur=r.top();r.pop();
			init+=cur.b-nowt;
			nowt=cur.b+cur.d;
			now+=cur.c;
		}
	}

	cout<<init<<endl;

 	return 0;
}

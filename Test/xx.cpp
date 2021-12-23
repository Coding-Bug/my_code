#include<iostream>
#include<string.h>
using namespace std;
#define Maxnum 115
int n;                       //结点数 
int re_a[Maxnum][Maxnum];    //存储人物关系，re_a[i][j]==1定义为i认识j 
int re_b[Maxnum][Maxnum];    //存储人物关系，re_b[i][j]==1定义为i与j不互相认识 
int coco[Maxnum];            //re_b[][]的连通分量，coco[i]==j定义为结点i在第j个连通分量中 
int sn;                      //re_b[][]的连通分量数 
int group[Maxnum];           //记录每个连通分量中的结点的分组，group[i]==j定义为结点i被分到分组j中，一共分两个组，所以j取1或者2 
int w[Maxnum];               //记录每个连通分量中两组结点数之差，用于dp
int g[Maxnum];               //记录每个结点被分到哪个队伍，g[i]==j定义为结点i被分到队伍j(j==1或者j==2) 


/* func：用深度优先遍历求图re_b的连通分量
*  parameter：now_point 当前被操作的结点
*             sn        连通分量的序号
*  return：none 
*/

void dfs(int now_point, int sn)
{
	coco[now_point] = sn;
	//给 与当前结点now_point在同一个连通分量的结点(即re_b[now_point][i]==1) 打上相同的序号
	for (int i = 1; i <= n; i++)
		if (coco[i] == 0 && re_b[now_point][i] == 1)
			dfs(i, sn);
}
/* func：对结点经行遍历，并利用dfs求re_b[][]的连通分量
*  parameter：none
*  return：none 
*/
void CoCo()
{
	sn = 0;
	memset(coco, 0, sizeof(coco));
	for (int i = 1; i <= n; i++)
		if (coco[i] == 0)
			dfs(i, ++sn);
}


/* func：将每个连通分量中的结点分为两个组，依据其在生成树中的深度的奇偶分到两个组中
*  parameter：coco_now   当前被操作的连通分量的序号
*             point_now  当前被操作的结点
*             group_id   当前被操作的结点被分入的组号，取值只有1或者2
*  return：none 
*/
void DivideIntoTwoGroups(int coco_now, int point_now, int group_id)
{
	group[point_now] = group_id;
	for (int i = 1; i <= n; i++)
		if (group[i] == 0 && coco[i] == coco_now && re_b[point_now][i])
			DivideIntoTwoGroups(coco_now, i, 3 - group_id);
}

/* func：判断问题是否有解，若同一分组中的两个结点在反图re_b[][]中有边，则无解
*  parameter：none
*  return：none 
*/
bool HasSolution()
{
	memset(group, 0, sizeof(group));
	int g1;              //记录每个连通分量组1的结点个数 
	int g2;              //记录每个连通分量组2的结点个数
	for (int i = 1; i <= sn; i++)
	{
		//分组 
		for (int j = 1; j <= n; j++)
		{
			if (coco[j] == i)
			{
				DivideIntoTwoGroups(i, j, 1);
				break;
			}
		}
		//统计两组中的结点数
		g1 = 0;
		g2 = 0;
		for (int j = 1; j <= n; j++)
		{
			if (coco[j] == i && group[j] == 1)	g1++;
			if (coco[j] == i && group[j] == 2)	g2++;
		}
		//将节点数多的放到第一组，便于dp时记录结点分队情况 
		if (g1 < g2)
		{
			for (int j = 1; j <= n; j++)
				if (coco[j] == i)
					group[j] = 3 - group[j];
			g1 ^= g2;
			g2 ^= g1;
			g1 ^= g2;
		}
		w[i] = g1 - g2;
		//判断问题是否有解：同组的结点在图re_b中有边则无解
		bool flag = true;
		for (int j = 1; j <= n && flag; j++)
			if (g1 > 1 && coco[j] == i && group[j] == 1)
				for (int k = 1; k <= n; k++)
					if (k != j && coco[k] == coco[j] && group[k] == group[j])
						if (re_b[j][k])
							flag = false;
		for (int j = 1; j <= n && flag; j++)
			if (g2 > 1 && coco[j] == i && group[j] == 2)
				for (int k = 1; k <= n; k++)
					if (k != j && coco[k] == coco[j] && group[k] == group[j])
						if (re_b[j][k])
							flag = false;
		if (!flag)	return flag;
	}
	return true;
}

/* func：以动态规划的思想求解问题，问题类型为背包问题
*  parameter：none
*  return：none 
*/
void DynamicProgramming()
{
	int f[Maxnum];          //用于dp 
	memset(f, 0, sizeof(f));
	int p[Maxnum][Maxnum];          //记录路径
	memset(p, 0, sizeof(p));
	int sum_w = 0;
	int sum_1 = 0;
	for (int i = 1; i <= sn; i++)    sum_w += w[i];
	//第i个连通分量，背包容量为j的情况下最优结果 
	for (int i = 1; i <= sn; i++)
	{
		for (int j = w[i]; j <= sum_w/2; j++)
		{
			//装入背包表示将两组中结点多的分到第一队,而结点多的是第一组(在分组时是如此操作的) 
			if (f[j - 1] < f[j - w[i]] + w[i])
			{
				f[j] = f[j - w[i]] + w[i];
				p[i][j] = 1;
			}
			//不装表示将两组中结点少的分到第一队 
			else
			{
				f[j] = f[j - 1];
			}
		}
	}
	int i = sn, j = sum_w/2;
	while(i >= 0 && j >= 0)
	{
		if (p[i][j] == 1)
		{
			for (int k = 1; k <= n; k++)
			{
				if (coco[k] == i && group[k] == 1)
				{
					g[k] = 1;
					sum_1++;
				}
				if (coco[k] == i && group[k] == 2)
					g[k] = 2;
			}
			j -= w[i];
		}
		else
		{
			for (int k = 1; k <= n; k++)
			{
				if (coco[k] == i && group[k] == 2)
				{
					g[k] = 1;
					sum_1++;
				}
				if (coco[k] == i && group[k] == 1)
				{
					g[k] = 2;
				}
			}
		}
		i--;
	}
	cout << sum_1;
	for (int i = 1; i <= n; i++)
		if (g[i] == 1)
			cout << " " << i;
	cout << endl;
	cout << n - sum_1;
	for (int i = 1; i <= n; i++)
		if (g[i] == 2)
			cout << " " << i;
	cout << endl; 
}

int main()
{
  freopen("A.txt","r",stdin);
	int t;
	//输入数据，构建人物关系图 
	cin >> n;
	memset(re_a, 0, sizeof(re_a));
	for (int i = 1; i <= n; i++)
	{
		while (cin >> t, t != 0)
			re_a[i][t] = 1;
	}
	//根据人物关系图，构建反图 
	memset(re_b, 0, sizeof(re_b));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i != j && (re_a[i][j] == 0 || re_a[j][i] == 0))
			{
				re_b[i][j] = 1;
				re_b[j][i] = 1;
			}
		}
	}




	//利用深度优先遍历(dfs)求反图的连通分量 
	CoCo();
	//将每一个连通分量中的点都分成两组
	//判断问题是否有解，有解则利用动态规划的思想求之
	if (!HasSolution())
		cout << "No solution" << endl;
	else
		DynamicProgramming();

	return 0;
}

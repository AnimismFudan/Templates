//BZOJ 1086
//读入一棵树，对其分块，每块大小在[B,3B]内
//树上莫队维护链的信息时，可以不保存lca的信息，来简化实现过程
//带修改树上莫队O(N ^ (5/3))，排序时按l所在块、r所在块、操作时间t三关键字排序
//执行莫队算法时将时间也纳入考虑，不断执行、撤销修改操作
//块大小为O(N^(2/3))复杂度最优
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <bitset>
#include <vector>
#include <cstdio>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int N,B,x,y,s,len,pt,l,r;
int st[2010],ne[2010],go[2010],fa[2010];
int q[2010];
int wei[2010],num[2010],res[2000][2000];
void dfs(int x)
{
	for (int i=st[x];i;i=ne[i])
	if (go[i]!=fa[x])
	{
		dfs(go[i]);
		for (int j=1;j<=res[go[i]][0];j++)res[x][++res[x][0]]=res[go[i]][j];
		if (res[x][0]>B)
		{
			s++;
			for (int j=1;j<=res[x][0];j++)num[res[x][j]]=s;
			wei[s]=x;
			res[x][0]=0;
		}
	}
	res[x][++res[x][0]]=x;res[x][0]=res[x][0];
	if (res[x][0]>B)
	{
		s++;
		for (int j=1;j<=res[x][0];j++)num[res[x][j]]=s;
		wei[s]=x;
		res[x][0]=0;
	}
}
void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}
int main()
{
	freopen("royal.in","r",stdin);
	freopen("royal.out","w",stdout);
	scanf("%d%d",&N,&B);
	for (int i=1;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		Add(x,y);Add(y,x);
	}
	for (q[l=r=0]=1;l<=r;l++)
	{
		int x=q[l];
		for (int i=st[x];i;i=ne[i])
		if (go[i]!=fa[x])
		q[++r]=go[i],fa[go[i]]=x;
	}
	dfs(1);
	if (!s)
	{
		printf("0");
		return 0;
	}
	for (int i=1;i<=res[1][0];i++)num[res[1][i]]=s;
	printf("%d\n",s);
	for (int i=1;i<=N;i++)printf("%d ",num[i]);
	printf("\n");
	for (int i=1;i<=s;i++)printf("%d ",wei[i]);
	return 0;
}

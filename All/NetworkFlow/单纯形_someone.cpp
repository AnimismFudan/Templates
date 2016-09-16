//代码来源于BZOJ3112
//题意：
//战线可以看作一个长度为 n 的序列，现在需要在这个序列上建塔来防守敌兵
//在序列第i号位置上建一座塔有 Ci 的花费，且一个位置可以建任意多的塔，费用累加计算
//有 m 个区间[Li, Ri]，在第i个区间的范围内要建至少 Di 座塔 。求最少花费。

#include <cstdio>
int a[1005][10005],b[10005][2],N,M;

void pivot(int x,int y)
{
	int l=0;
	for (int i=0; i<=M; i++) if (a[x][i]&&i!=y) b[++l][0]=a[x][i],b[l][1]=i;
	for (int i=0,t; i<=N; i++) if (i!=x&&(t=a[i][y]))
	{
		for (int j=0; j<=l; j++) a[i][b[j][1]]-=t*b[j][0];
		a[i][y]*=-1;
	}
}

int simplex()
{
	for (int x,y,m;;)
	{
		m=-int(1e9);for (int i=1; i<=M; i++) if (a[0][i]>m) m=a[0][i],y=i;
		if (m<=0) return -a[0][0];
		m=int(1e9); for (int i=1; i<=N; i++) if (a[i][y]>0&&a[i][0]<m) m=a[i][0],x=i;
		pivot(x,y);
	}
}

void doit()
{	
	scanf("%d%d",&N,&M);
	for (int i=1; i<=N; i++) scanf("%d",&a[i][0]);//Ci数组
	for (int i=1,l,r; i<=M; i++)
	{
		scanf("%d%d%d",&l,&r,&a[0][i]);
		for (int j=l; j<=r; j++) a[j][i]=1;
	}
	printf("%d\n",simplex());
}

int main()
{
	doit();
	return 0;
}

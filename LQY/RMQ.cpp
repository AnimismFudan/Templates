#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int MaxN=100007;
const int MaxM=30;

int n,m,q;
int a[MaxN],g[MaxN][3];
int f[MaxN][MaxM];

int MaxNum(int a,int b)
{
    if(a>b) return a;
    return b;
}

int MinNum(int a,int b)
{
    if(a<b) return a;
    return b;
}

int Calc(int id,int a,int b)
{
    a=MaxNum(a,g[id][0]);
    b=MinNum(b,g[id][1]);
    return b-a+1;
}

int Query(int a,int b)
{
    int k=int(log((double)b-a+1)/log(2.0));
    if((1<<k)==b-a+1) k--;
    int maxn=MaxNum(f[a][k],f[b-(1<<k)+1][k]);
    maxn=MaxNum(maxn,Calc(a+(1<<k)-1,a,b));
    maxn=MaxNum(maxn,Calc(b-(1<<k)+1,a,b));
    maxn=MaxNum(maxn,Calc(a+(1<<k),a,b));
    maxn=MaxNum(maxn,Calc(b-(1<<k),a,b));
    return maxn;
}

void Init()
{
     int i,j,k;
     scanf("%d",&q);
     for(i=1;i<=n;i++)
         scanf("%d",a+i),f[i][0]=1;
     i=1;
     while(i<=n)
     {
          j=i+1;
          while(j<=n&&a[j]==a[i]) j++;
          for(k=i;k<j;k++) g[k][0]=i,g[k][1]=j-1;
          i=j;
     }
     m=int(log((double)n)/log(2.0));
     for(j=1;j<=m;j++)
         for(i=1;i+(1<<j)<=n+1;i++)
             f[i][j]=Query(i,i+(1<<j)-1);
     return;
}

void Solve()
{
     int i,a,b;
     for(i=1;i<=q;i++)
     {
         scanf("%d%d",&a,&b);
         printf("%d\n",Query(a,b));
     }
     return;
}

int main()
{
    freopen("frequent.in","r",stdin);
    freopen("frequent.out","w",stdout);
    scanf("%d",&n);
    while(n)
    {
         Init();
         Solve();
         scanf("%d",&n);
    }
    return 0;
}

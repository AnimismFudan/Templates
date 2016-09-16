#include <iostream>
using namespace std;

const int MaxN=101;

struct EdgeTp
{int adj;
 int next;
}g[MaxN];

int n,tot;
int first[MaxN],dfn[MaxN],low[MaxN],par[MaxN];

void addedge(int x,int y)
{tot++;
 g[tot].adj=y;
 g[tot].next=first[x];
 first[x]=tot;
}

void init()
{int x,y;
 scanf("%d",&n);
 tot=0;
 while (scanf("%d %d",&x,&y)!=EOF)
   {addedge(x,y);
	addedge(y,x);
   }
 tot=0;
}

void dfs(int u,int p)
{int v,t;
 dfn[u]=low[u]=++tot;
 par[u]=p;
 t=first[u];
 while (t!=0)
   {v=g[t].adj;
    if (!dfn[v]) //��֦��
      {dfs(v,u);
       low[u]=min(low[u],low[v]);
      }
    else
      if (v!=p && dfn[v]<low[u]) //�����
        low[u]=dfn[v];
    t=g[t].next;
   }
}

void solve()
{int i,u,v,rc=0,gdc=0;//rcΪ���ڵ�������,gdcΪ����� 
 bool flag[MaxN]={false};//����Ƿ�Ϊ��� 
 dfs(1,0);
 for (v=2;v<=n;v++)
   {u=par[v];
    if (u==1)//uΪ���� 
      rc++;
    else//u��Ϊ���� 
      if (dfn[u]<=low[v])
        flag[u]=true;
   }
 if (rc>=2)
   flag[1]=true;
 for (i=1;i<=n;i++)
   if (flag[i])
     gdc++;
 printf("%d\n",gdc);
 for (i=1;i<=n;i++)
   if (flag[i])
     printf("%d\n",i);
}

int main()
{freopen("gd.in","r",stdin);
 freopen("gd.out","w",stdout);
 init();
 solve();
 return 0;
}

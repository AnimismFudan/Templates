#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

const int MaxN=1007;

int n,m,rt;
vector<int> iv[MaxN],qry[MaxN];
int cnt[MaxN],fa[MaxN]; bool vis[MaxN];

void Init()
{
     int i,id,t,chd,a,b;
     char st1[MaxN],st2[MaxN];
     for(i=1;i<=n;i++)
     {
         cnt[i]=fa[i]=0; vis[i]=false;
         iv[i].clear(); qry[i].clear();
     }
     for(i=1;i<=n;i++)
     {
         scanf("%d:(%d)",&id,&t);
         while(t--)
         {
               scanf("%d",&chd);
               //cout<<id<<' '<<chd<<endl;
               iv[id].push_back(chd);
               fa[chd]=id;
         }
     }
     for(i=1;i<=n;i++)
         if(!fa[i]) rt=i;
         else fa[i]=0;
     scanf("%d",&m);
     for(i=1;i<=m;i++)
     {
         scanf("%1s%d%d%s",st1,&a,&b,st2);
         //cout<<a<<' '<<b<<endl;
         qry[a].push_back(b);
         qry[b].push_back(a);
     }
     return;
}

int FindF(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=FindF(fa[x]);
}

void Tarjan(int u)
{
     int i,j;
     fa[u]=u;
     for(i=0;i<iv[u].size();i++)
     {
         j=iv[u][i];
         if(!fa[j])
         {
            Tarjan(j);
            fa[j]=u;
         }
     }
     vis[u]=true;
     for(i=0;i<qry[u].size();i++)
     {
         j=qry[u][i];
         if(vis[j]) cnt[FindF(j)]++;
     }
     return;
}

void Solve()
{
     int i;
     Tarjan(rt);
     for(i=1;i<=n;i++)
         if(cnt[i]) printf("%d:%d\n",i,cnt[i]);
     return;
}

int main()
{
    freopen("cca.in","r",stdin);
    freopen("cca.out","w",stdout);
    while(scanf("%d",&n)!=EOF)
    {
          Init();
          Solve();
    }
    return 0;
}

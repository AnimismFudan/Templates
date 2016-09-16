#include<iostream>
#include<cstdio>
using namespace std;

const int MaxN=6000;
const int MaxM=300000;
const int oo=1000000000;

typedef struct {int u,v,f,w,nxt,bck;} node;

int N,s,t,maxflow,mincost;
int tot,fir[MaxN];
node edg[MaxM];
int d[MaxN],fr,re,q[MaxN],lnk[MaxN];
bool inq[MaxN];

void AddEdge(int u,int v,int c,int w)
{
     //cout<<u<<' '<<v<<' '<<c<<' '<<w<<endl;
     tot++;
     edg[tot].u=u; edg[tot].v=v;
     edg[tot].f=c; edg[tot].w=-w;
     edg[tot].nxt=fir[u]; fir[u]=tot;
     edg[tot].bck=tot+1;
     tot++;
     edg[tot].u=v; edg[tot].v=u;
     edg[tot].f=0; edg[tot].w=w;
     edg[tot].nxt=fir[v]; fir[v]=tot;
     edg[tot].bck=tot-1;
     return;
}

bool BFS()
{
     int i,j,u;
     for(i=1;i<=N;i++) d[i]=oo;
     d[s]=0; fr=0; re=1;
     q[re]=s; inq[s]=true;
     while(fr!=re)
     {
           fr=(fr+1)%MaxN; u=q[fr];
           for(i=fir[u];i;i=edg[i].nxt)
           {
               j=edg[i].v;
               if(edg[i].f>0&&d[j]>d[u]+edg[i].w)
               {
                  d[j]=d[u]+edg[i].w;
                  lnk[j]=i;
                  if(!inq[j])
                  {
                     re=(re+1)%MaxN;
                     q[re]=j; inq[j]=true;
                  }
               }
           }
           inq[u]=false;
     }
     return (d[t]!=oo);
}

void Adjust()
{
     int i,f,w;
     for(i=t,f=oo;i!=s;i=edg[lnk[i]].u)
         f=min(f,edg[lnk[i]].f);
     for(i=t,w=0;i!=s;i=edg[lnk[i]].u)
     {
         edg[lnk[i]].f-=f;
         edg[edg[lnk[i]].bck].f+=f;
         w+=edg[lnk[i]].w;
     }
     maxflow+=f;
     mincost+=f*w;
     return;
}

int n,k;

void Init()
{
     int i,j,w;
     scanf("%d%d",&n,&k);
     N=n*n*2; s=++N,t=++N;
     AddEdge(s,1,k,0);
     AddEdge(n*n*2,t,k,0);
     for(i=1;i<=n;i++)
         for(j=1;j<=n;j++)
         {
             scanf("%d",&w);
             AddEdge(2*((i-1)*n+j)-1,2*((i-1)*n+j),1,w);
             AddEdge(2*((i-1)*n+j)-1,2*((i-1)*n+j),k-1,0);
         }
     for(i=1;i<=n;i++)
         for(j=1;j<=n;j++)
         {
             if(j<n) AddEdge(2*((i-1)*n+j),2*((i-1)*n+j)+1,k,0);
             if(i<n) AddEdge(2*((i-1)*n+j),2*(i*n+j)-1,k,0);
         }
     return;
}

void Solve()
{
     while(BFS()) Adjust();
     printf("%d",-mincost);
     return;
}

int main()
{
    freopen("POJ3422.in","r",stdin);
    freopen("POJ3422.out","w",stdout);
    Init();
    Solve();
    return 0;
}

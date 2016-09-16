#include<iostream>
#include<cstdio>
using namespace std;

const int MaxN=
const int MaxM=
const int oo=1000000000;

typedef struct {int adj,flo,nxt,bck;} node;

int N,s,t,maxflow;
node edg[MaxM];
int tot,fir[MaxN];
int level[MaxN],fr,re,q[MaxN];
int tp,st[MaxN],lnk[MaxN];

void AddEdge(int u,int v,int c)
{
     tot++;
     edg[tot].adj=v; edg[tot].flo=c;
     edg[tot].nxt=fir[u]; fir[u]=tot;
     edg[tot].bck=tot+1;
     tot++;
     edg[tot].adj=u; edg[tot].flo=0;
     edg[tot].nxt=fir[v]; fir[v]=tot;
     edg[tot].bck=tot-1;
     return;
}

bool Makelevel()
{
     int i,u;
     for(i=1;i<=N;i++) level[i]=-1;
     level[s]=1;
     fr=re=1; q[fr]=s;
     while(fr<=re)
     {
          u=q[fr++];
          for(i=fir[u];i;i=edg[i].nxt)
          {
              if(edg[i].flo>0&&level[edg[i].adj]==-1)
              {
                 level[edg[i].adj]=level[u]+1;
                 if(edg[i].adj==t) return true;
                 q[++re]=edg[i].adj;
              }
          }
     }
     return false;
}

void Dinic()
{
     int i,u,f;
     for(i=1;i<=N;i++) lnk[i]=fir[i];
     st[tp=1]=s;
     while(tp)
     {
          u=st[tp];
          if(u!=t)
          {
             for(i=lnk[u];i;i=edg[i].nxt)
                 if(edg[i].flo>0&&level[edg[i].adj]==level[u]+1)
                    break;
             if(i) lnk[u]=i,st[++tp]=edg[i].adj;
             else level[u]=-1,tp--;
          }
          else
          {
              f=oo;
              for(i=1;i<tp;i++) f=min(f,edg[lnk[st[i]]].flo);
              maxflow+=f;
              for(i=1;i<tp;i++)
              {
                  edg[lnk[st[i]]].flo-=f;
                  edg[edg[lnk[st[i]]].bck].flo+=f;
              }
              for(tp=1;edg[lnk[st[tp]]].flo>0;tp++);
          }
     }
     return;
}

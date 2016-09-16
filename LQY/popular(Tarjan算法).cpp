#include <iostream>
#define min(a,b) a>b ? b:a
using namespace std;

const int maxn=10001;
const int maxm=50001;

struct EdgeTp
{int adj;
 int next;
}g[maxm];

int n,m,tot,top,ans;
int first[maxn],dfn[maxn],low[maxn];
int stack[maxn],link[maxn],del[maxn];//del[]缩点标志

void init()
{int i,x,y;
 freopen("popular.in","r",stdin);
 freopen("popular.out","w",stdout);
 memset(first,0,sizeof(first));
 scanf("%d %d",&n,&m);
 tot=0;
 for (i=1;i<=m;i++)//存边表
   {scanf("%d %d",&x,&y);
    tot++;
    g[tot].adj=y;
    g[tot].next=first[x];
    first[x]=tot; 
   }
 memset(dfn,0,sizeof(dfn));
 memset(del,0,sizeof(del)); 
 tot=0;
 top=0;
 ans=0;
}

void dfs(int x) //求强连通分量
{int i,t,y;
 bool  flag;
 dfn[x]=++tot;
 low[x]=tot; //设置节点信息
 stack[++top]=x;
 link[x]=top;//入栈，记录该元素在栈中的位置
 flag=true; 
 t=first[x]; //依次遍历它对应的每条出边
 while (t!=0)
   {y=g[t].adj;
    if (dfn[y]==0) //若该点未被访问过
      {dfs(y);
       low[x]=min(low[x],low[y]); //更新low
      }
    else
      if (link[y]!=0)
        low[x]=min(low[x],dfn[y]); //如果该点被访问了，则该弧为后向弧或交叉弧，若处于一个连通分量里，则更新low
    t=g[t].next;
   }
 if (low[x]==dfn[x]) //如果low=dfn，则求出强连通分量
   {for (i=link[x];i<=top;i++)
      del[stack[i]]=x; //先将强连通分量缩成一个点
    for (i=link[x];i<=top;i++) //检查出度是否为0
      {t=first[stack[i]];
       while (t!=0)
         {if (del[g[t].adj]!=x)
            break; //若某条弧对应的点不在该强连通分量内，则有出度，跳出
          t=g[t].next;
         }
       if (t!=0) //若t不为0则证明有出度，设置flag为false
         {flag=false;
          break;
         }
      }
    if (flag) //若flag为true，则找到一个出度为0的强连通分量}
     {if (ans!=0)//如果ans已经被更新了，则代表有多于1个的出度为0的强连通分量，输出0
        ans=0;  
      else
        ans=top-link[x]+1; //反之，更新ans
     }
    t=top;
    top=link[x]-1; //top指针退回
    for (i=link[x];i<=t;i++)
      link[stack[i]]=0; //由于该连通分量中的点已经不在连通分量里了，所以进行撤销赋值
   }
}

int main()
{int i;
 init();
 for (i=1;i<=n;i++)
   if (dfn[i]==0)
     dfs(i);
 printf("%d\n",ans);
 return 0;
}

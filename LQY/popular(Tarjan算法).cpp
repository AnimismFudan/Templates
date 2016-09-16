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
int stack[maxn],link[maxn],del[maxn];//del[]�����־

void init()
{int i,x,y;
 freopen("popular.in","r",stdin);
 freopen("popular.out","w",stdout);
 memset(first,0,sizeof(first));
 scanf("%d %d",&n,&m);
 tot=0;
 for (i=1;i<=m;i++)//��߱�
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

void dfs(int x) //��ǿ��ͨ����
{int i,t,y;
 bool  flag;
 dfn[x]=++tot;
 low[x]=tot; //���ýڵ���Ϣ
 stack[++top]=x;
 link[x]=top;//��ջ����¼��Ԫ����ջ�е�λ��
 flag=true; 
 t=first[x]; //���α�������Ӧ��ÿ������
 while (t!=0)
   {y=g[t].adj;
    if (dfn[y]==0) //���õ�δ�����ʹ�
      {dfs(y);
       low[x]=min(low[x],low[y]); //����low
      }
    else
      if (link[y]!=0)
        low[x]=min(low[x],dfn[y]); //����õ㱻�����ˣ���û�Ϊ���򻡻򽻲满��������һ����ͨ����������low
    t=g[t].next;
   }
 if (low[x]==dfn[x]) //���low=dfn�������ǿ��ͨ����
   {for (i=link[x];i<=top;i++)
      del[stack[i]]=x; //�Ƚ�ǿ��ͨ��������һ����
    for (i=link[x];i<=top;i++) //�������Ƿ�Ϊ0
      {t=first[stack[i]];
       while (t!=0)
         {if (del[g[t].adj]!=x)
            break; //��ĳ������Ӧ�ĵ㲻�ڸ�ǿ��ͨ�����ڣ����г��ȣ�����
          t=g[t].next;
         }
       if (t!=0) //��t��Ϊ0��֤���г��ȣ�����flagΪfalse
         {flag=false;
          break;
         }
      }
    if (flag) //��flagΪtrue�����ҵ�һ������Ϊ0��ǿ��ͨ����}
     {if (ans!=0)//���ans�Ѿ��������ˣ�������ж���1���ĳ���Ϊ0��ǿ��ͨ���������0
        ans=0;  
      else
        ans=top-link[x]+1; //��֮������ans
     }
    t=top;
    top=link[x]-1; //topָ���˻�
    for (i=link[x];i<=t;i++)
      link[stack[i]]=0; //���ڸ���ͨ�����еĵ��Ѿ�������ͨ�������ˣ����Խ��г�����ֵ
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

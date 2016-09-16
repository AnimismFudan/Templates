#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int MaxN=100007;

typedef struct {int id,fa,ch[26],fail; bool isw;} NodeTp;

int n,m,l,root,tot,idx;
char str[MaxN]; int id[MaxN];
NodeTp trie[MaxN];
vector<int> iv[MaxN],qry[MaxN][2];
int fr,re,q[MaxN];
int indx,L[MaxN<<1],R[MaxN<<1],C[MaxN<<1];
int ans[MaxN];

void Add(int a,int b) {trie[a].fail=b; iv[b].push_back(a); return;}

void MakeAC()
{
     int u,i;
     fr=re=1; q[re]=root; trie[root].fail=root;
     while(fr<=re)
     {
           u=q[fr++];
           for(i=0;i<26;i++)
               if(trie[u].ch[i])
               {
                  if(u==root) Add(trie[u].ch[i],root);
                  else Add(trie[u].ch[i],trie[trie[u].fail].ch[i]);
                  q[++re]=trie[u].ch[i];
               }
               else
               {
                   if(u==root) trie[u].ch[i]=root;
                   else trie[u].ch[i]=trie[trie[u].fail].ch[i];
               }
     }
     return;
}

void DFS(int x)
{
     int i;
     L[x]=++indx;
     for(i=0;i<iv[x].size();i++)
         DFS(iv[x][i]);
     R[x]=++indx;
     return;
}

void Updata(int x,int d) {for(x;x&&x<=n;x+=x&(x^(x-1))) C[x]+=d; return;}
int Calc(int x) {int s=0; for(x;x>0;x-=x&(x^(x-1))) s+=C[x]; return s;}

int main()
{
    freopen("type.in","r",stdin);
    freopen("type.out","w",stdout);
    int i,j,k,p,x,y;
    root=tot=1;
    scanf("%s",str+1); l=strlen(str+1);
    j=root;
    for(i=1;i<=l;i++)
    {
        if(str[i]=='B') j=trie[j].fa;
        else if(str[i]=='P') trie[j].isw=true,id[++idx]=j;
        else
        {
            if(!trie[j].ch[str[i]-'a'])
               trie[j].ch[str[i]-'a']=++tot,trie[tot].fa=j;
            j=trie[j].ch[str[i]-'a'];
        }
    }
    scanf("%d",&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y),x=id[x],y=id[y],qry[y][0].push_back(x),qry[y][1].push_back(i);
    }
    MakeAC();
    DFS(1);
    n=indx<<1; p=1;
    for(i=1;i<=l;i++)
    {
        if(str[i]=='B') Updata(L[p],-1),p=trie[p].fa;
        else if(str[i]=='P')
        {
             j=p;
             for(k=0;k<qry[j][0].size();k++)
             {
                 ans[qry[j][1][k]]=Calc(R[qry[j][0][k]])-Calc(L[qry[j][0][k]]-1);
             }
        }
        else p=trie[p].ch[str[i]-'a'],Updata(L[p],1);
    }
    for(i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}

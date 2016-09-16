//最小树形图，就是给有向带权图中指定一个特殊的点root，求一棵以root为根的有向生成树T，并且T中所有边的总权值最小。
//题意：
//N个点M条边的有向图
//找到点x使其能到达所有其它点
//并且需要经过的边权和最小
//边权为0或1
//输出方案中边权为1的边

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int mm=120000;
struct ppp{
    int x,y,co,a,b,use,link;
} e[mm],q[1200000];
int i,j,k,l,n,m,be[mm],bo[mm],root,in[mm],pre[mm],ans,last[mm],
    nn,tot;
int Deric_MST(){
    root=1;
    int i,j,k,M,res=0;
    while(true){
        //zhao zui xiao ru du bian
        for(i=1;i<=n;++i)in[i]=1e9,bo[i]=be[i]=last[i]=0;
        for(i=1;i<=m;++i)if(e[i].x!=e[i].y && e[i].y!=root && e[i].co<in[e[i].y]){
            in[e[i].y]=e[i].co;
            pre[e[i].y]=e[i].x;
            last[e[i].y]=e[i].link;
        }
        for(i=1;i<=n;++i){
            if(i!=root && in[i]==1e9)return -1;
            if(i!=root)res+=in[i];
        }
    //  for(i=1;i<=n;++i)printf("%d %d\n",i,pre[i]);
    //  printf("\n");
        //suo dian
        M=0;
        for(i=1;i<=n;++i)if(i!=root){
            q[last[i]].use++;
            for(j=i;bo[j]!=i&&j!=root&&be[j]==0;j=pre[j])bo[j]=i;
            if(j!=root && be[j]==0){
                M++;
                for(k=j;pre[k]!=j;k=pre[k])be[k]=M;
                be[k]=M;
            }
        }
        if(M==0)return res;
        for(i=1;i<=n;++i)if(be[i]==0)be[i]=++M;
        //geng xing bian
        for(i=1;i<=m;++i){
            int v=e[i].y;
            e[i].x=be[e[i].x];
            e[i].y=be[e[i].y];
            if(e[i].x!=e[i].y){
                e[i].co-=in[v];
                q[++tot]=e[i];
                q[tot].use=0;
                q[tot].a=e[i].link;
                q[tot].b=last[v];
                e[i].link=tot;
            }
        }
        n=M;
        root=be[root];
//      printf("%d\n",n);
    }
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&m);
    nn=n;
    for(i=1;i<=m;++i){
        scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].co);
        q[++tot]=e[i];
        e[i].link=tot;
    }
    ans=Deric_MST();
    if(ans==-1)printf("-1\n");
    else{
        printf("%d\n",ans);
        for(i=tot;i>m;--i){
            q[q[i].a].use+=q[i].use;
            q[q[i].b].use-=q[i].use;
        }
        for(i=1;i<=m;++i)if(q[i].co==1 && q[i].use>0)printf("%d ",i);
    }
}
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int MaxN=1007;

typedef struct {int x,y;} node;

int n,m,l,mq[MaxN];
double dis;
node zr[MaxN];

inline int Chaji(node a,node b,node c) 
{
       return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}

int Cmp(const void *a,const void *b)
{
    node m=*(node*)a;
    node n=*(node*)b;
    int tmp=Chaji(zr[0],m,n);
    if(tmp==0) return m.x-n.x;
    return tmp;
}

void Init()
{
     int i; node t;
     scanf("%d%d",&n,&l);
     for(i=0;i<n;i++)
     {
         scanf("%d%d",&zr[i].x,&zr[i].y);
         if(zr[i].x<zr[0].x) t=zr[0],zr[0]=zr[i],zr[i]=t;
         if(zr[i].x==zr[0].x&&zr[i].y<zr[0].y) t=zr[0],zr[0]=zr[i],zr[i]=t;
     }
     n--;
     qsort(zr+1,n,sizeof(node),Cmp);
     //for(i=0;i<=n;i++)
     //    cout<<zr[i].x<<' '<<zr[i].y<<endl;
     //cout<<endl;
     return;
}

inline double Dis(node a,node b)
{
       return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y));
}

void Solve()
{
     int i;
     ++m; mq[m]=0;
     ++m; mq[m]=1;
     i=2;
     while(i<=n)
     {
          while(m>2&&Chaji(zr[mq[m-1]],zr[mq[m]],zr[i])>=0) m--;
          mq[++m]=i; i++;
     }
     //for(i=1;i<=m;i++)
     //    cout<<zr[mq[i]].x<<' '<<zr[mq[i]].y<<endl;
     for(i=1;i<m;i++)
         dis+=Dis(zr[mq[i]],zr[mq[i+1]]);
     dis+=Dis(zr[mq[m]],zr[mq[1]]);
     dis+=2*3.1415926535*l;
     printf("%.0lf",dis);
     return;
}

int main()
{
    freopen("wall.in","r",stdin);
    freopen("wall.out","w",stdout);
    Init();
    Solve();
    return 0;
}

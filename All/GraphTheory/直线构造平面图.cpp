//读入若干条直线，构造平面图，并计算每一块区域的面积
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
const double eps=1e-8;
bool vis[500010];
int st[10010],ne[500010],go[500010],inv[500010];
int temp[500010];
double area[500010],ans[500010];
int Test,N,M,len,pt,Pathlen;
class poi{public:double x,y;int n;}P[10010],Q[10010];
class seg{public:poi s,t;}Line[110];
class way{public:int x,y,num;double ta;}Path[500010];

bool cmp1(const poi &a,const poi &b){return a.x+eps<b.x||(fabs(b.x-a.x)<=eps&&a.y<b.y);}
bool cmp2(const way &a,const way &b){return a.x<b.x||(a.x==b.x&&a.ta<b.ta);}

double xet(double sx,double sy,double tx,double ty){return sx*ty-tx*sy;}
double dist(const poi &a){return sqrt(a.x*a.x+a.y*a.y);}

void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;area[pt]=xet(P[x].x,P[x].y,P[y].x,P[y].y)/2;}

bool cross(const seg &a,const seg &b,poi &d){
	if (fabs(xet(a.t.x-a.s.x,a.t.y-a.s.y,b.t.x-b.s.x,b.t.y-b.s.y))<=eps)return 0;
	double s1=xet(a.t.x-a.s.x,a.t.y-a.s.y,b.s.x-a.s.x,b.s.y-a.s.y);
	double s2=xet(a.t.x-a.s.x,a.t.y-a.s.y,b.t.x-a.s.x,b.t.y-a.s.y);
	d.x=(-b.s.x*s2+b.t.x*s1)/(s1-s2);
	d.y=(-b.s.y*s2+b.t.y*s1)/(s1-s2);
	return 1;
}

void Getcross(){
	poi d;
	d.x=d.y=d.n=0;
	M=0;
	for (int i=0;i<N;i++)for (int j=0;j<N;j++)if (cross(Line[i],Line[j],d))P[M++]=d;
	sort(P,P+M,cmp1);
	len=0;
	for (int i=1;i<M;i++)if (fabs(P[i].x-P[len].x)>eps||fabs(P[i].y-P[len].y)>eps)P[++len]=P[i];
	len++;M=len;
	for (int i=0;i<M;i++)P[i].n=i;
}
void Getway(){
	Pathlen=0;
	for (int i=0;i<N;i++){
		len=0;
		for (int j=0;j<M;j++)
			if (fabs(xet(P[j].x-Line[i].s.x,P[j].y-Line[i].s.y,P[j].x-Line[i].t.x,P[j].y-Line[i].t.y))<eps)
				Q[len++]=P[j];
		sort(Q,Q+len,cmp1);
		for (int j=1;j<len;j++){
			Path[Pathlen].x=Q[j-1].n;
			Path[Pathlen].y=Q[j].n;
			Path[Pathlen].num=Pathlen;
			Path[Pathlen].ta=atan2(Q[j].y-Q[j-1].y,Q[j].x-Q[j-1].x);
			Pathlen++;
			Path[Pathlen].x=Q[j].n;
			Path[Pathlen].y=Q[j-1].n;
			Path[Pathlen].num=Pathlen;
			Path[Pathlen].ta=atan2(Q[j-1].y-Q[j].y,Q[j-1].x-Q[j].x);
			Pathlen++;
		}
	}
	sort(Path,Path+Pathlen,cmp2);
	for (int i=0;i<Pathlen;i++){
		Add(Path[i].x,Path[i].y);
		temp[Path[i].num]=pt;
	}
	for (int i=1;i<=pt;i++)inv[i]=temp[Path[i-1].num^1];
}
void Getarea(){
	len=0;
	for (int i=1;i<=pt;i++)vis[i]=1;
	for (int i=1;i<=pt;i++)
		if(vis[i]){
			double size=0;
			int x=i;
			while (vis[x]){
				vis[x]=0;
				size+=area[x];
				x=ne[inv[x]];
				if (x<=0)
					x=st[-x];
			}
			if (size>1e-8)ans[len++]=size;
		}
	printf("%d\n",len);
	sort(ans,ans+len);
	for (int i=0;i<len;i++)printf("%.6lf\n",ans[i]);
}
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d",&Test);
	while (Test--){
		scanf("%d",&N);
		for (int i=0;i<N;i++)scanf("%lf%lf%lf%lf",&Line[i].s.x,&Line[i].s.y,&Line[i].t.x,&Line[i].t.y);
		Getcross();
		for (int i=0;i<M;i++)st[i]=-i;pt=0;
		Getway();
		Getarea();
		if (Test)printf("\n");
	}
}

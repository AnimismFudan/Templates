#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 100;
const double eps = 1e-7;
const double PI = acos(-1.0);

struct NodeTp
{
    double x,y;
    NodeTp() {};
    NodeTp(double x,double y):x(x),y(y){}
    void Print() {printf("%.2lf %.2lf\n",x,y);}
};

int n,m,x,y,x1,y11,x2,y2;
double r,sumarea,dis[MaxN];
NodeTp O,nod[MaxN],area[MaxN];

inline double Distance(NodeTp A,NodeTp B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

inline double Cross(NodeTp A,NodeTp B)
{
    //printf("Triangle: \n"); A.Print(); B.Print(); printf("\n");
    return A.x*B.y-B.x*A.y;
}

inline double Sector(NodeTp A,NodeTp B)
{
    //printf("Sector: \n"); A.Print(); B.Print(); printf("\n");
    double phiA=atan2(A.y,A.x),phiB=atan2(B.y,B.x);
    double phi=phiB-phiA;
    if(phi>PI) phi-=PI*2;
    if(phi<-PI) phi+=PI*2;
    return phi*r*r*.5;
}

void Calc(NodeTp A,NodeTp B)
{
    //printf("Calc :  \n"); A.Print(); B.Print(); printf("\n");
    double a = (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
    double b = 2*((B.x-A.x)*A.x+(B.y-A.y)*A.y);
    double c = A.x*A.x+A.y*A.y-r*r, d = b*b-4*a*c;
    area[++m]=A;
    if(d<-eps) return;
    d = sqrt(d);
    double t1 = (-b+d)/(a+a);
    double t2 = -(b+d)/(a+a);
    if(t1>t2) swap(t1,t2);
    // printf("(%.3lf, %.3lf)\n", t1, t2);
    if(t1>eps&&t1<1-eps) area[++m]=NodeTp(A.x+(B.x-A.x)*t1,A.y+(B.y-A.y)*t1);
    if(t2>eps&&t2<1-eps) area[++m]=NodeTp(A.x+(B.x-A.x)*t2,A.y+(B.y-A.y)*t2);
    return;
}

int main()
{
    freopen("mammoth.in","r",stdin);
    freopen("mammoth.out","w",stdout);
    scanf("%d%d%lf",&x,&y,&r);
    scanf("%d%d%d%d",&x1,&y11,&x2,&y2);
    O.x=0.0; O.y=0.0;
    nod[1].x=x1-x,nod[1].y=y11-y; nod[2].x=x2-x,nod[2].y=y11-y;
    nod[3].x=x2-x,nod[3].y=y2-y; nod[4].x=x1-x,nod[4].y=y2-y; n=4;
    for(int i=1;i<n;i++) Calc(nod[i],nod[i+1]); 
    Calc(nod[n],nod[1]);
    area[++m]=area[1];
    //for(int i=1;i<=m;i++) area[i].Print(); printf("\n"); 
    for(int i=1;i<m;i++)
        if(hypot((area[i].x+area[i+1].x)*.5,(area[i].y+area[i+1].y)*.5)>r-eps)
            sumarea+=Sector(area[i],area[i+1]);
        else sumarea+=Cross(area[i],area[i+1])*.5;
    printf("%.12lf\n",fabs(sumarea));
    return 0;
}

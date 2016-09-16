//work函数可计算出被覆盖i次的圆面积并，储存于ans[i]中
//复杂度O(N^2*log(N))
//实现方式为有向面积并
//弓形切割+内部有向多边形面积
//包含函数：
//弓形面积sector
//点积dot 叉积xet
//向量旋转Rotate
//两圆求交点getcross,返回值void，结果存于d1、d2中，flag表示各种情况
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const double pi = 3.1415926535897932384626433832795;
int N, len;
double ans1, ans2, ans[100010];
class poi {
  public:
	double x, y;
} d1, d2;
class cir {
  public:
	poi p;
	double r;
} P[100010];
class rec {
  public:
	poi p;
	int t;
	double ta;
} q[100010];
bool cmp (const rec &a, const rec &b) {
	return a.ta < b.ta || (a.ta == b.t && a.t < b.t);
}
double sector (cir a, double alpha) {
	double res1 = a.r * a.r * alpha / 2;
	double res2 = a.r * a.r * sin (alpha) / 2;
	return res1 - res2;
}
double dot (poi a, poi b) {
	return a.x * b.x + a.y * b.y;
}
double xet (poi a, poi b) {
	return a.x * b.y - b.x * a.y;
}
void Rotate (poi a, poi &b, double alpha) {
	b.x = a.x * cos (alpha) - a.y * sin (alpha);
	b.y = a.x * sin (alpha) + a.y * cos (alpha);
}
void getcross (cir a, cir b, poi &d1, poi &d2, int &flag) {
	poi d;
	double dist, co, alpha, timi;
	d.x = b.p.x - a.p.x;
	d.y = b.p.y - a.p.y;
	dist = sqrt (dot (d, d) );
	if (dist >= a.r + b.r) {
		flag = 0;
		return;
	}
	if (dist + b.r <= a.r) {
		flag = 0;
		return;
	}
	if (dist + a.r <= b.r) {
		flag = 1;
		return;
	}
	co = (a.r * a.r + dist * dist - b.r * b.r) / a.r / dist / 2;
	alpha = acos (co);
	timi = a.r / dist;
	Rotate (d, d1, -alpha);
	d1.x *= timi;
	d1.y *= timi;
	d1.x += a.p.x;
	d1.y += a.p.y;
	Rotate (d, d2, alpha);
	d2.x *= timi;
	d2.y *= timi;
	d2.x += a.p.x;
	d2.y += a.p.y;
	flag = 2;
}
void work() {
	int r, delta, flag, now;
	for (int i = 1; i <= N; i++) {
		delta = now = r = 0;
		q[++r].p.x = P[i].p.x - P[i].r;
		q[r].p.y = P[i].p.y;
		q[r].t = 1;
		q[r].ta = -pi;
		q[++r].p.x = P[i].p.x - P[i].r;
		q[r].p.y = P[i].p.y;
		q[r].t = -1;
		q[r].ta = pi;
		for (int j = 1; j <= N; j++)
			if (i != j) {
				getcross (P[i], P[j], d1, d2, flag);
				if (flag == 0) continue; //相离或P[j]被P[i]包含
				if (flag == 1) {
					delta++;    //P[i]被P[j]包含
					continue;
				}
				q[++r].p = d1;
				q[r].t = 1;
				q[r].ta = atan2 (q[r].p.y - P[i].p.y, q[r].p.x - P[i].p.x);
				q[++r].p = d2;
				q[r].t = -1;
				q[r].ta = atan2 (q[r].p.y - P[i].p.y, q[r].p.x - P[i].p.x);
				if (q[r - 1].ta > q[r].ta) now++;
			}
		sort (q + 1, q + r + 1, cmp);
		for (int j = 1; j <= r; j++) {
			now += q[j].t;
			int step = now + delta;
			double alpha = q[j % r + 1].ta - q[j].ta;
			if (alpha < 0) alpha += 2 * pi;
			ans[step] += sector (P[i], alpha);
			ans[step] += xet (q[j].p, q[j % r + 1].p) / 2;
		}
	}
}
int main() {
	freopen ("B.in", "r", stdin);
	freopen ("B.out", "w", stdout);
	scanf ("%d", &N);
	for (int i = 1; i <= N; i++) scanf ("%lf%lf%lf", &P[i].p.x, &P[i].p.y, &P[i].r);
	work();
	for (int i = 1; i <= N; i++)
		if (i & 1) ans1 += ans[i] - ans[i + 1];
		else ans2 += ans[i] - ans[i + 1];
//	printf("%.10lf %.10lf\n",ans1,ans2);
	printf ("%.5lf %.5lf\n", ans1, ans2);
}

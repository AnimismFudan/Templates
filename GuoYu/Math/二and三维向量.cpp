#include <set>
#include <map>
#include <ctime>
#include <queue>
#include <cmath>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
const double eps = 1e-7;
class poi {
  public:
	double x, y;
	poi() {}
	poi (const double &x, const double &y) : x (x), y (y) {}
	void read() {
		scanf ("%lf%lf", &x, &y);
	}
	void clr() {
		x = 2e9;
		y = 2e9;
	}
	poi rotate (double selta) {
		poi c;
		c.x = x * cos (selta) - y * sin (selta);
		c.y = x * sin (selta) + y * cos (selta);
		return c;
	}
	poi operator + (const poi &X) const {
		poi c;
		c.x = x + X.x;
		c.y = y + X.y;
		return c;
	}
	poi operator - (const poi &X) const {
		poi c;
		c.x = x - X.x;
		c.y = y - X.y;
		return c;
	}
	poi operator * (double k) const {
		poi c;
		c.x = x * k;
		c.y = y * k;
		return c;
	}
	poi operator / (double k) const {
		poi c;
		c.x = x / k;
		c.y = y / k;
		return c;
	}
} p0, p1, a0, a1;
class cir {
  public:
	poi s;
	double r;
	cir (const poi &s, const double &r) : s (s), r (r) {}
};
class line {
  public:
	poi s, t;
	line () {}
	line (const poi &s, const poi &t) : s (s), t (t) {}
};
class poi3 {
  public:
	double x, y, z;
	poi3() {}
	poi3 (const double &x, const double &y, const double &z) : x (x), y (y), z (z) {}
	void read() {
		scanf ("%lf%lf%lf", &x, &y, &z);
	}
	void pri() {
		printf ("%lf %lf %lf", x, y, z);
	}
	void clr() {
		x = 2e9;
		y = 2e9;
		z = 2e9;
	}
	poi3 rotatex (double selta) {
		poi3 c;
		c.x = x;
		c.y = y * cos (selta) - z * sin (selta);
		c.z = y * sin (selta) + z * cos (selta);
		return c;
	}
	poi3 rotatey (double selta) {
		poi3 c;
		c.y = y;
		c.z = z * cos (selta) - x * sin (selta);
		c.x = z * sin (selta) + x * cos (selta);
		return c;
	}
	poi3 rotatez (double selta) {
		poi3 c;
		c.z = z;
		c.x = x * cos (selta) - y * sin (selta);
		c.y = x * sin (selta) + y * cos (selta);
		return c;
	}
	poi3 operator + (const poi3 &X) const {
		poi3 c;
		c.x = x + X.x;
		c.y = y + X.y;
		c.z = z + X.z;
		return c;
	}
	poi3 operator - (const poi3 &X) const {
		poi3 c;
		c.x = x - X.x;
		c.y = y - X.y;
		c.z = z - X.z;
		return c;
	}
	poi3 operator * (double k) const {
		poi3 c;
		c.x = x * k;
		c.y = y * k;
		c.z = z * k;
		return c;
	}
	poi3 operator / (double k) const {
		poi3 c;
		c.x = x / k;
		c.y = y / k;
		c.z = z / k;
		return c;
	}
} C0, C1, P0, P1, A, A0, A1, T0;
double S0, S1, R;
int dcmp (double x) {
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}
double dot (poi a, poi b) {
	return a.x * b.x + a.y * b.y;
}
double xet (poi a, poi b) {
	return a.x * b.y - b.x * a.y;
}
double dist (poi a, poi b) {
	return sqrt (dot (b - a, b - a) );
}
double dist (poi a, line l) {
	return fabs (xet (l.t - l.s, a - l.s) / dist (l.s, l.t) );
}
double dot (poi3 a, poi3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
double dist (poi3 a, poi3 b) {
	return sqrt (dot (b - a, b - a) );
}
void cross (cir c, line l, poi &a0, poi &a1) {
	a0.clr();
	a1.clr();
	double d = dist (c.s, l);
	if (dcmp (d - c.r) > 0) return;
	double dd = dist (l.s, l.t);
	double t = dot (l.t - l.s, c.s - l.s) / dd;
	poi p = (l.t - l.s) / dd * t + l.s;
	poi v = (l.t - l.s) / dist (l.s, l.t);
	double L = sqrt (c.r * c.r - d * d);
	a0 = p + v * L;
	a1 = p - v * L;
}
void getAz() {
	double Tan = (P1.z - P0.z) / dist (p0, p1);
	A.z = dist (p0, poi (A.x, A.y) ) * Tan + P0.z;
	if (dcmp (A.z - C1.z) > 0 || dcmp (A.z - C0.z) < 0) A.clr();
}
void getAc (const poi3 &C, poi3 &A) {
	A.clr();
	if (!dcmp (P0.z - P1.z) ) {
		if (!dcmp (P0.z - C.z) ) A = P0;
		return;
	}
	if (dcmp (P0.z - P1.z) < 0 && dcmp (P0.z - C.z) <= 0) {
		A.x = (P1.x - P0.x) / (P1.z - P0.z) * (C.z - P0.z) + P0.x;
		A.y = (P1.y - P0.y) / (P1.z - P0.z) * (C.z - P0.z) + P0.y;
		A.z = C.z;
	}
	if (dcmp (P0.z - P1.z) > 0 && dcmp (P0.z - C.z) >= 0) {
		A.x = (P1.x - P0.x) / (P1.z - P0.z) * (C.z - P0.z) + P0.x;
		A.y = (P1.y - P0.y) / (P1.z - P0.z) * (C.z - P0.z) + P0.y;
		A.z = C.z;
	}
	if (dcmp (dist (A, C) - R) > 0) A.clr();
}
int main() {
	freopen ("tracing.in", "r", stdin);
	freopen ("tracing.out", "w", stdout);
	C0.read();
	C1.read();
	scanf ("%lf", &R);
	P0.read();
	P1.read();
	T0 = C0;
	C0 = C0 - T0;
	C1 = C1 - T0;
	P0 = P0 - T0;
	P1 = P1 - T0;
	S0 = atan2 (C1.y, C1.x);
	C0 = C0.rotatez (-S0);
	C1 = C1.rotatez (-S0);
	P0 = P0.rotatez (-S0);
	P1 = P1.rotatez (-S0);
	S1 = atan2 (C1.x, C1.z);
	C0 = C0.rotatey (-S1);
	C1 = C1.rotatey (-S1);
	P0 = P0.rotatey (-S1);
	P1 = P1.rotatey (-S1);
	p0 = poi (P0.x, P0.y), p1 = poi (P1.x, P1.y);
	if (dcmp (dist (p0, p1) ) > 0) {
		cross (cir (poi (0, 0), R), line (p0, p1), a0, a1);
		if (dcmp (dot (p1 - p0, a0 - p0) ) < 0) a0.clr();
		if (dcmp (dot (p1 - p0, a1 - p0) ) < 0) a1.clr();
		if (dcmp (dist (a0, p0) - dist (a1, p0) ) < 0) A.x = a0.x, A.y = a0.y;
		else A.x = a1.x, A.y = a1.y;
		if (fabs (A.x) > 1e9 && fabs (A.y) > 1e9) {
			printf ("NONE\n");
			return 0;
		}
		getAz();
		getAc (C0, A0);
		getAc (C1, A1);
		if (dcmp (dist (A, P0) - dist (A0, P0) ) > 0) A = A0;
		if (dcmp (dist (A, P0) - dist (A1, P0) ) > 0) A = A1;
		if (fabs (A.x) > 1e9 && fabs (A.y) > 1e9) {
			printf ("NONE\n");
			return 0;
		}
	} else {
		A = P0;
		if (dcmp (dist (poi (A.x, A.y), poi (0, 0) ) - R) > 0) {
			printf ("NONE\n");
			return 0;
		}
		if (dcmp (P0.z - P1.z) < 0) {
			A.z = 2e9;
			if (dcmp (C0.z - P0.z) >= 0) A.z = min (A.z, C0.z);
			if (dcmp (C1.z - P0.z) >= 0) A.z = min (A.z, C1.z);
			if (dcmp (P0.z - C0.z) *dcmp (P0.z - C1.z) <= 0) A.z = min (A.z, P0.z);
			if (A.z >= 1e9) {
				printf ("NONE\n");
				return 0;
			}
		} else {
			A.z = -2e9;
			if (dcmp (C0.z - P0.z) <= 0) A.z = max (A.z, C0.z);
			if (dcmp (C1.z - P0.z) <= 0) A.z = max (A.z, C1.z);
			if (dcmp (P0.z - C0.z) *dcmp (P0.z - C1.z) <= 0) A.z = min (A.z, P0.z);
			if (A.z <= -1e9) {
				printf ("NONE\n");
				return 0;
			}
		}
	}
	A = A.rotatey (S1);
	A = A.rotatez (S0);
	A = A + T0;
	A.pri();
}

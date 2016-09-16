#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
using namespace std;

const int con = 100000;
#define pi 3.141592653589793238462643383l
int N, lena, lenb, test;
int rev[600010];
char sa[600010], sb[600010];
class complex {
  public:
	long double re, im;
	void getdata (long double x, long double y) {
		re = x;
		im = y;
	}
	complex operator + (const complex &X) {
		complex c;
		c.re = re + X.re;
		c.im = im + X.im;
		return c;
	}
	complex operator - (const complex &X) {
		complex c;
		c.re = re - X.re;
		c.im = im - X.im;
		return c;
	}
	complex operator * (const complex &X) {
		complex c;
		c.re = re * X.re - im * X.im;
		c.im = re * X.im + im * X.re;
		return c;
	}
} a[600010], b[600010], W[2][600010];

void FFT (complex *a, int f) {
	complex x, y;
	for (int i = 0; i < N; i++) if (i < rev[i]) swap (a[i], a[rev[i]]);
	for (int i = 1; i < N; i <<= 1) {
		for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
			for (int k = 0, l = 0; k < i; l += t, k++) {
				x = W[f][l] * a[j + k + i], y = a[j + k];
				a[j + k] = y + x;
				a[j + k + i] = y - x;
			}
	}
	if (f) for (int i = 0; i < N; i++) a[i].re /= N;
}

int main() {
	freopen ("2179.in", "r", stdin);
	freopen ("2179.out", "w", stdout);
	scanf ("%d", &lena);
	scanf ("%s%s", sa, sb);
	lena = strlen (sa);
	lenb = strlen (sb);
	for (int i = 0; i <= (lena - 1) / 5; i++)
		for (int j = 4; j >= 0; j--)
			if (lena - i * 5 - j > 0)
				a[i].re = a[i].re * 10 + sa[lena - 1 - i * 5 - j] - '0';
	lena = (lena - 1) / 5 + 1;
	for (int i = 0; i <= (lenb - 1) / 5; i++)
		for (int j = 4; j >= 0; j--)
			if (lenb - i * 5 - j > 0)
				b[i].re = b[i].re * 10 + sb[lenb - 1 - i * 5 - j] - '0';
	lenb = (lenb - 1) / 5 + 1;
	for (N = 1; N < lena || N < lenb; N <<= 1);
	N <<= 1;
	for (int i = 0; i < N; i++) {
		int x = i, y = 0;
		for (int k = 1; k < N; x >>= 1, k <<= 1) (y <<= 1) |= x & 1;
		rev[i] = y;
	}
	for (int i = 0; i < N; i++) {
		W[0][i].getdata (cos (2 * pi * i / N), sin (2 * pi * i / N) );
		W[1][i].im = -W[0][i].im;
		W[1][i].re = W[0][i].re;
	}
	FFT (a, 0);
	FFT (b, 0);
	for (int i = 0; i < N; i++)
		a[i] = a[i] * b[i];
	FFT (a, 1);
	for (int i = 0; i < N; i++) {
		long double t = (a[i].re + 0.5) / con;
		t = floor (t);
		a[i].re = a[i].re - t * con;
		if (abs (a[i].re) < 1e-3) a[i].re = 0;
		a[i + 1].re = a[i + 1].re + t;
	}
	while (N && abs (a[N].re) < 1e-3) N--;
	printf ("%.0lf", double (a[N].re) );
	for (int i = N - 1; i >= 0; i--) {
//		if (fabs(a[i].re)<1e-3)a[i].re=0;
		printf ("%05.0lf", double (a[i].re) );
	}
}

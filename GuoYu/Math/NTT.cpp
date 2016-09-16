#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define intl long long
const LL P = 998244353;
const LL G = 3;
int N, M, Test;
LL W[2][400010];
LL A[400010], B[400010], fac[400010], ni[400010], po[400010];
int rev[400010];
int a[400010];

LL Pow (LL a, LL b) {
	LL c = 1;
	for (; b; b >>= 1, a = a * a % P)
		if (b & 1) c = c * a % P;
	return c;
}

void FFT (LL *a, int f) {
	for (int i = 0; i < M; i++)
		if (i < rev[i]) swap (a[i], a[rev[i]]);
	for (int i = 1; i < M; i <<= 1)
		for (int j = 0, t = M / (i << 1); j < M; j += i << 1)
			for (int k = 0, l = 0; k < i; k++, l += t) {
				LL x, y;
				x = W[f][l] * a[j + k + i] % P;
				y = a[j + k];
				a[j + k] = (y + x) % P;
				a[j + k + i] = (y - x + P) % P;
			}
	if (f)
		for (int i = 0, x = Pow (M, P - 2); i < M; i++)
			a[i] = a[i] * x % P;
}

void work() {
	for (int i = 0; i < M; i++) {
		int x = i, y = 0;
		for (int k = 1; k < M; x >>= 1, k <<= 1) (y <<= 1) |= x & 1;
		rev[i] = y;
	}
	W[0][0] = W[1][0] = 1;
	LL x = Pow (G, (P - 1) / M), y = Pow (x, P - 2);
	for (int i = 1; i < M; i++) {
		W[0][i] = x * W[0][i - 1] % P;
		W[1][i] = y * W[1][i - 1] % P;
	}
}

void Init() {
	memset (A, 0, sizeof (A) );
	memset (B, 0, sizeof (B) );
	for (int i = 0; i <= N - 1; i++) B[i] = ni[i];
	for (int i = 0; i <= N - 1; i++) {
		A[i] = a[N - i];
		A[i] *= fac[N - i - 1];
		A[i] %= P;
		A[i] *= po[i];
		A[i] %= P;
	}
}

void pri() {
	for (int i = 0; i < N; i++) printf ("%I64d ", A[i]);
	putchar ('\n');
}

int main() {
	freopen ("I.in", "r", stdin);
	freopen ("I.out", "w", stdout);
	scanf ("%d", &Test);
	fac[0] = 1LL;
	po[0] = 1LL;

	for (int i = 1; i <= 100000; i++) po[i] = po[i - 1] * 2LL % P;
	for (int i = 1; i <= 100000; i++) fac[i] = fac[i - 1] * (intl) i % P;

	ni[100000] = Pow (fac[100000], P - 2LL);

	for (int i = 99999; i >= 0; i--)
		ni[i] = (ni[i + 1] * (intl) (i + 1) ) % P;

	for (int tt = 1; tt <= Test; tt++) {
		scanf ("%d", &N);
		for (M = 1; M <= N; M <<= 1);
		M <<= 1;
		for (int i = 1; i <= N; i++) scanf ("%d", &a[i]);
		sort (a + 1, a + N + 1);
		reverse (a + 1, a + N + 1);
		Init();

		work();

		FFT (A, 0);
		FFT (B, 0);
		for (int i = 0; i < M; i++) A[i] = A[i] * B[i] % P;
		FFT (A, 1);

		for (int i = 0; i < N; i++) A[i] = (A[i] * ni[N - i - 1]) % P;
		reverse (A, A + N);
		for (int i = 1; i < N; i++) A[i] += A[i - 1], A[i] %= P;
		pri();
	}
	return 0;
}

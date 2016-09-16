#include <complex>
//递归版本

typedef complex <double> comp;
const double pi = acos (-1.0);

void FFT (comp a[], int n, int sign) {
	if (n == 1) return;
	for (int i = 0; i < n; i++) js[i] = a[i];
	int N = n >> 1;
	for (int i = 0; i < N; i++) a[i] = js[i << 1], a[i + N] = js[i << 1 | 1];

	FFT (a, N, sign);
	FFT (a + N, N, sign);
	double p = 2.0 * pi / n * sign;
	comp u = 1, base = comp (cos (p), sin (p) );

	for (int i = 0; i < N; i++) {
		js[i] = a[i] + a[i + N] * u;
		js[i + N] = a[i] - a[i + N] * u;
		u = u * base;
	}

	for (int i = 0; i < n; i++) a[i] = js[i];
}

int main() {
	for (N = 1; N >> 1 < n; N <<= 1);
	swap (n, N);
	FFT (a, n, 1);
	FFT (b, n, 1);
	for (int i = 0; i < n; i++) a[i] *= b[i];
	FFT (a, n, -1);
	for (int i = 0; i < n; i++) a[i] /= n;
	return 0;
}

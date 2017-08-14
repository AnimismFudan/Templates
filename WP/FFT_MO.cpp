struct CP {
	double a, b;
	CP operator + (const CP &y) const { return (CP) { a + y.a, b + y.b }; }
	CP operator - (const CP &y) const { return (CP) { a - y.a, b - y.b }; }
	CP operator * (const CP &y) const { return (CP) { a * y.a - b * y.b, a * y.b + b * y.a }; }
	CP operator !() const { return (CP) { a, -b }; };
};
	
namespace FFT_MO {
	const int FFT_MAXN = (1 << 18);
	const double pi = 3.14159265358979323846264338327950288L;
	CP nw[FFT_MAXN + 1], f[FFT_MAXN], g[FFT_MAXN], t[FFT_MAXN];
	int bitrev[FFT_MAXN];

	void dft(CP *a, int n, int flag = 1) {
		int d = 0; while ((1 << d) * n != FFT_MAXN) d++;
		for (int i = 0; i < n; i++)
			if (i < (bitrev[i] >> d))
				swap(a[i], a[bitrev[i] >> d]);
		for (int l = 2; l <= n; l <<= 1) {
			int del = FFT_MAXN / l * flag;
			for (int i = 0; i < n; i += l) {
				CP *le = a + i, *ri = a + i + (l >> 1), *w = flag == 1 ? nw : nw + FFT_MAXN;
				for (int k = 0; k < (l >> 1); k++) {
					CP ne = *ri * *w;
					*ri = *le - ne, *le = *le + ne;
					le++, ri++, w += del;
				}
			}
		}
		if (flag != 1)
			for (int i = 0; i < n; i++) a[i].a /= n, a[i].b /= n;
	}

	void fft_init() {
		int L = 0; while ((1 << L) != FFT_MAXN) L++;
		bitrev[0] = 0;
		for (int i = 1; i < FFT_MAXN; i++)
			bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
		for (int i = 0; i < FFT_MAXN + 1; i++)
			nw[i] = (CP) { (double) cosl(2 * pi / FFT_MAXN * i), (double) sinl(2 * pi / FFT_MAXN * i) };
	}

	void convo(intl *a, int n, intl *b, int m, intl *c) {
		for (int i = 0; i <= n + m; i++) c[i] = 0;
		int N = 2;
		while (N <= n + m) N <<= 1;
		for (int i = 0; i < N; i++) {
			int aa = (i <= n) ? a[i] : 0, bb = (i <= m) ? b[i] : 0;
			if (aa < 0) a += Mo; if (bb < 0) b += Mo;
			f[i] = (CP) { (double) (aa >> 15), (double) (aa & 32767) };
			g[i] = (CP) { (double) (bb >> 15), (double) (bb & 32767) };
		}
		dft(f, N); dft(g, N);
		for (int i = 0; i < N; i++) {
			int j = i ? N - i : 0;
			t[i] = ((f[i] + !f[j]) * (!g[j] - g[i]) + (!f[j] - f[i]) * (g[i] + !g[j])) * (CP) { 0, 0.25 };
		}
		dft(t, N, -1);
		for (int i = 0; i <= n + m; i++) {
			(c[i] += ((intl) (t[i].a + 0.5)) % Mo << 15) %= Mo;
			if (c[i] < 0) c[i] += Mo;
		}
		for (int i = 0; i < N; i++) {
			int j = i ? N - i : 0;
			t[i] = (!f[j]-f[i])*(!g[j]-g[i])*(CP) {-0.25,0} + (CP) {0,0.25} * (f[i] + !f[j]) * (g[i] + !g[j]);
		}
		dft(t, N, -1);
		for (int i = 0; i <= n + m; i++) {
			c[i] += (intl) (t[i].a + 0.5) + ((intl) (t[i].b + 0.5) % Mo << 30);
			c[i] = (c[i] % Mo + Mo) % Mo;
		}
	}
};

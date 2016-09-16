//按通常方法连边后，在执行网络流前先执行
//	ans=greedy();
int greedy() {
	for (int i = 1; i <= N; i++) rank[i] = i;
	sort (rank + 1, rank + N + 1, cmp);
	memset (in, 0, sizeof (in) );
	memset (out, 0, sizeof (out) );
	in[S] = oo;
	for (int i = 1; i <= N; i++) {
		int x = rank[i];
		for (int j = st[x]; j; j = ne[j])
			if ( (! (j & 1) ) && in[x] > out[x]) {
				int t = min (in[x] - out[x], c[j]);
				in[go[j]] += t;
				out[x] += t;
			}
	}
	memset (in, 0, sizeof (in) );
	in[T] = oo;
	for (int i = N; i; i--) {
		int x = rank[i];
		for (int j = st[x]; j; j = ne[j])
			if ( (j & 1) && out[go[j]] > in[go[j]]) {
				int t = min (min (out[go[j]] - in[go[j]], in[x]), c[j ^ 1]);
				in[go[j]] += t;
				in[x] -= t;
				c[j] += t;
				c[j ^ 1] -= t;
			}
	}
	return in[S];
}

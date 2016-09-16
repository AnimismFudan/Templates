
void Add (int x, int y, int cc) {
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
}

bool build() {
	for (int i = S; i <= T; i++) dist[i] = -1;
	dist[S] = 0;
	q[l = r = 0] = S;
	for (; l <= r; l++) {
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i] && dist[go[i]] == -1) {
				dist[go[i]] = dist[x] + 1;
				if (go[i] == T) return 1;
				q[++r] = go[i];
			}
	}
	return 0;
}

int dinic (int x, int up) {
	if (x == T) return up;
	int w = 0;
	for (int i = st[x]; w < up && i; i = ne[i])
		if (c[i] && dist[go[i]] == dist[x] + 1) {
			int t = dinic (go[i], min (up - w, c[i]) );
			w += t;
			c[i] -= t;
			c[i ^ 1] += t;
		}
	if (!w) dist[x] = -1;
	return w;
}

int main() {
	scanf ("%d%d", &N, &M);
	pt = 1;
	for (int i = 1; i <= M; i++) {
		scanf ("%d%d%d%d", &P[i].x, &P[i].y, &P[i].l, &P[i].r);
		Add (P[i].x, P[i].y, P[i].r - P[i].l);
		Add (P[i].y, P[i].x, 0);
		in[P[i].y] += P[i].l;
		out[P[i].x] += P[i].l;
	}
	S = 0;
	T = N + 1;
	for (int i = 1; i <= N; i++) {
		if (in[i] > out[i]) Add (S, i, in[i] - out[i]), Add (i, S, 0);
		if (in[i] < out[i]) Add (i, T, out[i] - in[i]), Add (T, i, 0);
	}
	while (build() )
		ans += dinic (S, oo);
}

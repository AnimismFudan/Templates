
void antiflow (int x) {
	for (int i = S; i <= T; i++) dist[i] = -1;
	dist[x] = 0;
	for (q[l = r = 0] = x; l <= r && dist[T] == -1; l++) {
		int x = q[l];
		for (int i = st[x]; i; i = ne[i])
			if (c[i ^ 1] && dist[go[i]] == -1) {
				dist[go[i]] = dist[x] + 1;
				p[go[i]] = i;
				if (go[i] == T) break;
				q[++r] = go[i];
			}
	}
	for (int i = T; i != x; i = go[p[i] ^ 1])
		c[p[i]]++, c[p[i] ^ 1]--;
	c[num[x]]++;
	c[num[x] ^ 1]--;
}

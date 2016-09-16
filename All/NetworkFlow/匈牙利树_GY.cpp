
bool find (int x) {
	vis[x] = 0;
	for (int i = st[x]; i; i = ne[i])
		if (vis[go[i]]) {
			vis[go[i]] = 0;
			if (!pre[go[i]] || (vis[pre[go[i]]] && find (pre[go[i]]) ) ) {
				pre[go[i]] = x;
				return 1;
			}
		}
	return 0;
}

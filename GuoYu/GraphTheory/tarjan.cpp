
//tot, last, num
//mark[N]表示点x所在强连通块序号
//dfn[N]表示dfn序号
//low[N]表示点x能到的点的最小dfn
//sta[]为栈
//vis[]为点是否在栈内,是否出栈

void tarjan (int x) {
	dfn[x] = low[x] = ++tot;
	sta[++last] = x;
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (vis[go[i]] == 0) {
			tarjan (go[i]);
			low[x] = min (low[x], low[go[i]]);
		} else if (vis[go[i]] == 1) low[x] = min (low[x], dfn[go[i]]);
	if (dfn[x] == low[x]) {
		++num;
		int p;
		do {
			p = sta[last];
			mark[p] = num;
			vis[p] = 2;
			sta[last--] = 0;
		} while (p != x);
	}
}
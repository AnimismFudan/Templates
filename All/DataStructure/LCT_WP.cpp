bool home (int u) {
	return (fa[u] && (kid[fa[u]][0] == u || kid[fa[u]][1] == u) );
}
// 判断是不是根. 是根返回 false.
void rotate (int u) {
	int f = fa[u];
	int k = (kid[f][0] == u);
	fa[u] = fa[f];
	if (fa[f] && kid[fa[f]][0] == f) kid[fa[f]][0] = u;
	else if (fa[f] && kid[fa[f]][1] == f) kid[fa[f]][1] = u;
	kid[f][k ^ 1] = kid[u][k];
	if (kid[u][k]) fa[kid[u][k]] = f;
	fa[f] = u;
	kid[u][k] = f;
	update (f);
}
void splay (int u) {
	int f, ff;
	while (home (u) ) {
		f = fa[u];
		ff = fa[f];
		if (home (f) && ! ( (kid[f][0] == u) ^ (kid[ff][0] == f) ) ) rotate (f);
		rotate (u);
	}
	update (u);
}
void access (int u) {
	int v = 0;
	for ( ; u; u = fa[u]) {
		splay (u);
		kid[u][1] = v;
		update (v = u);
	}
}

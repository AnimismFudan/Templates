
//dfs实现spfa
//可判断是否出现负环
//返回0表示出现负环
//感觉好弱…

bool dfs (int x) {
	use[x] = 1;
	bool flag = 1;
	for (int i = st[x]; i; i = ne[i])
		if (dist[go[i]] < dist[x] + w[i]) {
			if (use[go[i]])
				return 0;
			dist[go[i]] = dist[x] + w[i];
			flag &= dfs (go[i]);
			if (!flag) return 0;
		}
	use[x] = 0;
	return 1;
}
bool bfs() {
	for (int i = 1; i <= t; i++) dis[i] = 1 << 29;
	dis[s] = 0;
	for (int i = 1; i <= t; i++) mark[i] = 0;
	que.push(s); mark[s] = 1;

	while (!que.empty()) {
		int u = que.front();
		que.pop(); mark[u] = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (!edge[i].cap) continue;
			if (dis[v] > dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				if (!mark[v]) {
					mark[v] = 1;
					que.push(v);
				}
			}
		}
	}

	return (dis[t] != (1 << 29));
}

int dfs(int u,int ma) {
	if (vis[u]) return 0;	
	if (u == t || !ma) return ma;
	vis[u] = 1;
	int f,flow = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (dis[v] == dis[u] + edge[i].cost && (f = dfs(v, min(edge[i].cap,ma)))) {
			flow += f; ma -= f;
			edge[i].cap -= f; edge[i ^ 1].cap += f;
			//ans += edge[i].cost * f;
			if (!ma) {
				vis[u] = 0;
				return flow;
			}
		}
	}
	vis[u] = 0;
	dis[u] = INF;
	return flow;
}

void solve() {	
	while(bfs()) {
		int flow = dfs(s,INF);
		ans += flow * dis[t];
	}
}

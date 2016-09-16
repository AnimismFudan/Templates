bool path(int u) {
	vis[u] = 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (sig(edge[i].len - Mark[u] - Mark[v])) {
			if (vis[v]) continue;
			vis[v] = 1;
			if (!nex[v] || path(nex[v])) {
				nex[v] = u, nex[u] = v;
				return true;
			}
		} else {
			slk[v] = min(slk[v], edge[i].len - Mark[u] - Mark[v]);
		}
	}
	return false;
}

void km() {
	for (int i = 1; i <= nl; i++) Mark[lp[i]] = INF;
	for (int i = 1; i <= nr; i++) Mark[rp[i]] = 0;
	for (int i = 1; i <= nl; i++) {
		int u = lp[i];
		for (int j = fst[u]; j; j = edge[j].nex) {
			Mark[u] = min(Mark[u], edge[j].len);
		}
	}

	for (int i = 1; i <= nl; i++) {
		int u = lp[i];
		for (int j = 1; j <= nr; j++)
			slk[rp[j]] = 1 << 28;
		for (int j = 1; j <= nl; j++)
			vis[rp[j]] = vis[lp[j]] = 0;

		while (!path(u)) {
			double sing = 1 << 28;
			for (int j = 1; j <= nr; j++) {
				int v = rp[j];
				if (!vis[v]) sing = min(sing, slk[v]);
			}

			for (int j = 1; j <= nl; j++) if (vis[lp[j]]) Mark[lp[j]] += sing;
			for (int j = 1; j <= nr; j++) if (vis[rp[j]]) Mark[rp[j]] -= sing;
			for (int j = 1; j <= nr; j++) slk[rp[j]] = 1 << 28, vis[rp[j]] = 0;
		}
	}

	for (int i = 1; i <= nl; i++) ans += Mark[lp[i]];
	for (int i = 1; i <= nr; i++) ans += Mark[rp[i]];	
}


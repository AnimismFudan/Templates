
//stack[]为栈
//ins[N]为点x是否在栈内
//b[x][y]为邻接矩阵

void dfs (int x) {
	vis[x] = 1;
	stack[++last] = x;
	ins[x] = 1;
	for (int i = 0; i < 26; i++)
		if (b[x][i]) {
			if (!vis[i]) {
				dfs (i);
				if (flag) return;
			} else if (ins[i]) {
				int p;
				do {
					p = stack[last];
					ans[++len] = p;
					stack[last--] = 0;
				} while (p != i);
				for (int j = 1; (j << 1) <= len; j++) swap (ans[j], ans[len - j + 1]);
				flag = 1;
				return;
			}
		}
	stack[last--] = 0;
	ins[x] = 0;
}
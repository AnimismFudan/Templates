#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#define LL long long
using namespace std;
int test, pt, N, M, P;
int st[810], ne[810], go[810], w[810], fa[810], depth[810];
int vis[810], pre[810], dx[810], dy[810], slack[810];
int b[410][410];
class rec {
  public:
	int x, y, w;
} line[810];
void Add (int x, int y, int ww) {
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}
void getdepth (int x) {
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != go[fa[x]]) {
			fa[go[i]] = i ^ 1;
			depth[go[i]] = depth[x] + 1;
			getdepth (go[i]);
		}
}
bool find (int x) {
	vis[x] = 1;
	for (int i = 1; i <= P; i++)
		if (dx[x] + dy[i] == b[x][i]) {
			if (!vis[P + i]) {
				vis[P + i] = 1;
				if (!pre[i] || (!vis[pre[i]] && find (pre[i]) ) ) {
					pre[i] = x;
					return 1;
				}
			}
		} else slack[x] = min (slack[x], dx[x] + dy[i] - b[x][i]);
	return 0;
}
int main() {
	freopen ("F.in", "r", stdin);
	freopen ("F.out", "w", stdout);
	scanf ("%d", &test);
	while (test--) {
		memset (st, 0, sizeof (st) );
		pt = 1;
		memset (fa, 0, sizeof (fa) );
		memset (depth, 0, sizeof (depth) );
		memset (b, 0, sizeof (b) );
		memset (pre, 0, sizeof (pre) );
		memset (dx, 0, sizeof (dx) );
		memset (dy, 0, sizeof (dy) );
		scanf ("%d%d", &N, &M);
		for (int i = 1; i < N; i++) {
			scanf ("%d%d%d", &line[i].x, &line[i].y, &line[i].w);
			Add (line[i].x, line[i].y, line[i].w);
			Add (line[i].y, line[i].x, line[i].w);
		}
		getdepth (1);
		P = max (N - 1, M - N + 1);
		for (int i = N; i <= M; i++) {
			scanf ("%d%d%d", &line[i].x, &line[i].y, &line[i].w);
			int x = line[i].x, y = line[i].y, ww = line[i].w;
			while (x != y) {
				if (depth[x] < depth[y]) swap (x, y);
				if (w[fa[x]] > ww)
					b[fa[x] / 2][i - N + 1] = w[fa[x]] - ww;
				x = go[fa[x]];
			}
		}
		for (int i = 1; i <= P; i++)
			for (int j = 1; j <= P; j++)
				dx[i] = max (dx[i], b[i][j]);
		for (int i = 1; i <= P; i++) {
			memset (vis, 0, sizeof (vis) );
			memset (slack, 127, sizeof (slack) );
			while (!find (i) ) {
				int res = 2e9;
				for (int j = 1; j <= P; j++) res = min (res, slack[j]);
				for (int j = 1; j <= 2 * P; j++)
					if (vis[j]) {
						if (j <= P) dx[j] -= res;
						else dy[j - P] += res;
					}
				memset (vis, 0, sizeof (vis) );
				memset (slack, 127, sizeof (slack) );
			}
		}
		for (int i = 1; i < N; i++)
			printf ("%d\n", line[i].w - dx[i]);
		for (int i = N; i <= M; i++)
			printf ("%d\n", line[i].w + dy[i - N + 1]);
		if (test) printf ("\n");
	}
}

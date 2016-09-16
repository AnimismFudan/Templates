//7.8 G
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
int ans, flow, Test, pt, l, r, S, T, N, x;
int st[110], ne[1010], go[1010], c[1010], w[1010], p[1010];
int dist[110], vis[110], q[100010];
void Add (int x, int y, int cc, int ww) {
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	c[pt] = cc;
	w[pt] = ww;
}
void cost() {
	ans = 0;
	for (;;) {
		for (int i = S; i <= T; i++) dist[i] = -2e9;
		q[l = r = 0] = S;
		vis[S] = true;
		dist[S] = 0;
		for (; l <= r; l++) {
			x = q[l];
			vis[x] = false;
			for (int i = st[x]; i; i = ne[i])
				if (c[i] && dist[go[i]] < dist[x] + w[i]) {
					dist[go[i]] = dist[x] + w[i];
					p[go[i]] = i;
					if (!vis[go[i]]) {
						vis[go[i]] = true;
						q[++r] = go[i];
					}
				}
		}
		if (dist[T] == -2e9) return;
		int Min = 2e9;
		for (int i = T; i != S; i = go[p[i] ^ 1])
			Min = min (Min, c[p[i]]);
		for (int i = T; i != S; i = go[p[i] ^ 1]) {
			c[p[i]] -= Min;
			c[p[i] ^ 1] += Min;
		}
		ans = ans + Min * dist[T];
		flow = flow + Min;
	}
}
int main() {
	freopen ("G.in", "r", stdin);
	freopen ("G.out", "w", stdout);
	scanf ("%d\n", &Test);
	while (Test--) {
		N = 11;
		memset (st, 0, sizeof (st) );
		pt = 1;
		S = 0;
		T = 2 * N + 1;
		for (int i = 1; i <= N; i++)
			Add (S, i, 1, 0), Add (i, S, 0, 0);
		for (int i = 1; i <= N; i++)
			Add (N + i, T, 1, 0), Add (T, N + i, 0, 0);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++) {
				scanf ("%d", &x);
				if (x)
					Add (i, N + j, 1, x),
						Add (N + j, i, 0, -x);
			}
		ans = 0;
		flow = 0;
		cost();
		printf ("%d\n", ans);
	}
}

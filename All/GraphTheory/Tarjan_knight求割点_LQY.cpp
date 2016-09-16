#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define maxn 1001
#define maxm 1000005
vector<int>vc[maxn];
stack<int>st;
vector<int>vec;
int maps[maxn][maxn];
int n, m;
struct list {
	int u;
	int e;
	int next;
} edge[maxm * 2];
int tops, head[maxm * 2], vis[maxm * 2];
int nums, dnf[maxn], low[maxn], instack[maxn], times;
int mark[maxn], odd[maxn], visit[maxn];

void Add (int x, int y) {
	edge[tops].u = x;
	edge[tops].e = y;
	edge[tops].next = head[x];
	head[x] = tops++;
}

void Init() {
	int a, b, i, j;
	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++)
			maps[i][j] = 0;
	for (i = 0; i < m; i++) {
		scanf ("%d%d", &a, &b);
		maps[a][b] = maps[b][a] = -1;
	}
	tops = 0;
	for (i = 0; i <= m * 2; i++) head[i] = -1;
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
			if (maps[i][j] == 0)
				Add (i, j), Add (j, i);
	return;
}

int Find (int x) {
	int i;
	for (i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (mark[y]) {
			if (visit[y] == -1) {
				visit[y] = (visit[x] + 1) % 2;
				if (Find (y) ) return 1;
			} else if (visit[x] == visit[y]) return 1;
		}
	}
	return 0;
}

void Dos (int x) {
	int i;
	memset (visit, -1, sizeof (visit) );
	visit[x] = 0;
	if (Find (x) ) {
		for (i = 0; i <= n; i++)
			if (mark[i]) odd[i] = 1;
	}
}

void Tarjan (int x) {
	int i;
	low[x] = dnf[x] = times++;
	for (i = head[x]; i != -1; i = edge[i].next) {
		if (vis[i]) continue;
		vis[i] = vis[i ^ 1] = 1;
		int y = edge[i].e;
		if (!dnf[y]) {
			st.push (i);
			Tarjan (y);
			low[x] = min (low[x], low[y]);
			if (low[y] >= dnf[x]) {
				memset (mark, 0, sizeof (mark) );
				int yw = 0;
				int cc = 0;
				while (1) {
					cc++;
					yw = st.top();
					st.pop();
					mark[edge[yw].e] = mark[edge[yw].u] = 1;
					if (edge[yw].u == x) break;
				}
				if (cc >= 3) Dos (x);
			}
		} else if (dnf[y] < dnf[x]) {
			st.push (i);
			low[x] = min (low[x], dnf[y]);
		}
	}
	return;
}

void Clear() {
	int i;
	for (i = 0; i <= n; i++) low[i] = dnf[i] = instack[i] = 0;
	for (i = 0; i <= n; i++) mark[i] = odd[i] = 0;
	nums = 0;
	times = 1;
	memset (vis, 0, sizeof (vis) );
	while (!st.empty() ) st.pop();
	vec.clear();
	return;
}

int Sum() {
	int i, s = 0;
	for (i = 1; i <= n; i++)
		if (odd[i]) s++;
	return s;
}

int main() {
	freopen ("knight.in", "r", stdin);
	freopen ("knight.out", "w", stdout);
	while (scanf ("%d%d", &n, &m) && (n || m) ) {
		Init();
		Clear();
		for (int i = 1; i <= n; i++)
			if (!dnf[i]) Tarjan (i);
		printf ("%d\n", n - Sum() );
	}
	return 0;
}

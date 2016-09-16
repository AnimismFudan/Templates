#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
using namespace std;
#define LL long long
void read (LL &x) {
	char ch = getchar();
	bool flag = false;
	while ( (ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-') {
		flag = true;
		ch = getchar();
	}
	x = 0;
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	if (flag) x = -x;
}
void read (int &x) {
	char ch = getchar();
	bool flag = false;
	while ( (ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-') {
		flag = true;
		ch = getchar();
	}
	x = 0;
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	if (flag) x = -x;
}
const LL pp = (1e9) + 7;
bool flag;
int N, M, pt, x, y, len, num, last, ans, res;
int stack[600010];
int used[600010], vis[600010], ins[600010];
int st[600010], now[600010], ne[600010], go[600010];
vector <int > cir[600010], zone[600010];
class line {
  public:
	int x, y, data;
} P[600010];
class rec {
  public:
	int r0, r1;
} p;
void Add (int x, int y) {
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}
void maketree() {
	memset (vis, 0, sizeof (vis) );
	memset (used, 0, sizeof (used) );
	for (int i = 1; i <= N; i++) now[i] = st[i];
	for (int head = 1; head <= N; head++) {
		for (stack[last = 1] = head, ins[head] = 1; last;) {
			int x = stack[last];
			flag = 1;
			for (int i = now[x]; i; i = ne[i]) {
				now[x] = ne[i];
				if (!used[i]) {
					used[i] = used[i ^ 1] = 1;
					if (ins[go[i]]) {
						int p = go[i];
						++num;
						while (ins[p]) {
							cir[num].push_back (stack[last]);
							ins[stack[last]] = 0;
							stack[last--] = 0;
						}
						for (int i = 0; i < cir[num].size(); i++) {
							++len;
							P[len].x = cir[num][i];
							P[len].data = num;
						}
					}
					stack[++last] = go[i];
					ins[stack[last]] = 1;
					flag = 0;
					break;
				}
			}
			if (flag) {
				if (last > 1) {
					++len;
					P[len].x = stack[last];
					P[len].y = stack[last - 1];
				}
				ins[stack[last]] = 0;
				stack[last--] = 0;
			}
		}
	}
}
rec work (int z, int head, int p) {
	vis[head]++;
	if (z) {
		int x = 0;
		while (cir[z][x] != head) x++;
		int f[2][2];
		f[0][0] = 0;
		f[0][1] = -2e9; //若head被取，则在之前已经计入答案
		f[1][0] = -2e9;
		f[1][1] = 0;
		rec t;
		for (int i = 1; i < cir[z].size(); i++) {
			int y = cir[z][ (x + i) % cir[z].size()];
			int r0 = 0, r1 = 1;
			vis[y]++;
			for (int j = 0; j < zone[y].size(); j++)
				if (zone[y][j] != z) {
					t = work (zone[y][j], y, 0);
					r0 += t.r0;
					r1 += t.r1;
				}
			for (int j = st[y]; j; j = ne[j]) {
				t = work (0, go[j], y);
				r0 += max (t.r0, t.r1);
				r1 += t.r0;
			}
			for (int j = 0; j < 2; j++) {
				t.r0 = max (f[j][0] + r0, f[j][1] + r0);
				t.r1 = f[j][0] + r1;
				f[j][0] = t.r0;
				f[j][1] = t.r1;
			}
		}
		t.r0 = max (f[0][0], f[0][1]);
		t.r1 = f[1][0];
		return t;
	} else {
		rec t, tt;
		t.r0 = 0;
		t.r1 = 1;
		for (int i = 0; i < zone[head].size(); i++) {
			tt = work (zone[head][i], head, 0);
			t.r0 += tt.r0;
			t.r1 += tt.r1;
		}
		for (int i = st[head]; i; i = ne[i]) {
			int y = go[i];
			if (y == p) continue;
			tt = work (0, go[i], head);
			t.r0 += max (tt.r0, tt.r1);
			t.r1 += tt.r0;
		}
		return t;
	}
}
register char *_sp __asm__ ("rsp");
int main() {
	const int size = 64 * 1024 * 1024;
	static char *sys, *mine (new char[size] + size - 4096);
	sys = _sp;
	_sp = mine;

	freopen ("4316.in", "r", stdin);
	freopen ("4316.out", "w", stdout);
	scanf ("%d%d", &N, &M);
	pt = 1;
	for (int i = 1; i <= M; i++)
		scanf ("%d%d", &x, &y), Add (x, y), Add (y, x);
	maketree();
	/*	printf("cir:\n");
		for (int i=1;i<=num;i++){
			for (int j=0;j<cir[i].size();j++)
				printf("%d ",cir[i][j]);
			printf("\n");
		}
		printf("line:\n");
		for (int i=1;i<=len;i++)
			printf("x:%d y:%d data:%d\n",P[i].x,P[i].y,P[i].data);*/
	memset (st, 0, sizeof (st) );
	pt = 1;
	for (int i = 1; i <= len; i++)
		if (P[i].data)
			zone[P[i].x].push_back (P[i].data);
		else Add (P[i].x, P[i].y), Add (P[i].y, P[i].x);
	memset (vis, 0, sizeof (vis) );
	ans = 0;
	for (int i = 1; i <= N; i++)
		if (!vis[i]) {
			rec p = work (0, i, 0);
			res = max (p.r0, p.r1);
			ans += res;
		}
	printf ("%d\n", ans);

	_sp = sys;
}

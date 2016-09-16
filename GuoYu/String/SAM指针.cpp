#include <set>
#include <map>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
const int maxc = 37;
class SAnode {
  public:
	SAnode *par, *go[maxc];
	int val;
	bool vis;
	SAnode() {
		par = NULL;
		val = 0;
		vis = 0;
		for (int i = 0; i < maxc; i++) go[i] = NULL;
	}
	SAnode (int _val) {
		par = NULL;
		val = _val;
		vis = 0;
		for (int i = 0; i < maxc; i++) go[i] = NULL;
	}
}*root, *SAlast;
void extend (int w) {
	SAnode *p = SAlast;
	SAnode *np = new SAnode (p->val + 1);
	while (p != NULL && p->go[w] == NULL)
		p->go[w] = np, p = p->par;
	if (p == NULL) np->par = root;
	else {
		SAnode *q = p->go[w];
		if (p->val + 1 == q->val) np->par = q;
		else {
			SAnode *nq = new SAnode (p->val + 1);
			memcpy (nq->go, q->go, sizeof (nq->go) );
			nq->par = q->par;
			q->par = nq;
			np->par = nq;
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->par;
		}
	}
	SAlast = np;
}
int text (char w) {
	if ('0' <= w && w <= '9') return w - '0';
	if ('A' <= w && w <= 'Z') return w - 'A' + 10;
	return 36;
}
int len, ans0, ans1, ans2;
char s[6010];
void search (SAnode *now) {
	if (now->vis) return;
	now->vis = 1;
	int num = 0;
	for (int i = 0; i < maxc; i++)
		if (now->go[i] != NULL) {
			num++;
			search (now->go[i]);
		}
	if (num > 1 && now != root) {
		ans0++;
		int ll = now->val;
		if (ll > ans1)
			ans1 = ll, ans2 = 0;
		if (ll == ans1) ans2++;
	}
}
int main() {
	freopen ("dna.in", "r", stdin);
	freopen ("dna.out", "w", stdout);
	scanf ("%s", s);
	root = SAlast = new SAnode (0);
	len = strlen (s);
	s[len++] = '$';
	for (int i = 0; i < len; i++)
		extend (text (s[i]) );
	search (root);
	printf ("%d\n%d\n%d", ans0, ans1, ans2);
}

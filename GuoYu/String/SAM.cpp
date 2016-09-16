
const int maxc = 10;
class SAnode {
  public:
	int fa, l, go[maxc];
	void clr() {
		memset (go, 0, sizeof (go) );
		fa = l = 0;
	}
};
class sam {
  public:
	int root, size;
	SAnode a[4000010];
	void pre() {
		root = size = 1;
		a[1].clr();
	}
	int init (int last, int x) {
		int np = ++size;
		int r, p, q;
		a[np].clr();
		a[np].l = a[last].l + 1;
		for (p = last; p && !a[p].go[x]; p = a[p].fa) a[p].go[x] = np;
		if (!p) a[np].fa = root;
		else {
			q = a[p].go[x];
			if (a[q].l == a[p].l + 1) a[np].fa = q;
			else {
				r = ++size;
				a[r].clr();
				a[r].fa = a[q].fa;
				a[r].l = a[p].l + 1;
				memcpy (a[r].go, a[q].go, sizeof (a[r].go) );
				a[q].fa = a[np].fa = r;
				for (; p && a[p].go[x] == q; p = a[p].fa)
					a[p].go[x] = r;
			}
		}
		return np;
	}
} SA;

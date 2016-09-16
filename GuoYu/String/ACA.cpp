
const int maxc = 4;
class ACAnode {
  public:
	int go[maxc];
	int fail, acc;
	void clr() {
		memset (go, 0, sizeof (go) );
		fail = acc = 0;
	}
};
class ACA {
  public:
	int root, size;
	ACAnode a[1010];
	void pre() {
		root = size = 1;
		a[1].clr();
	}
	int init (int last, int x) {
		if (!a[last].go[x]) {
			a[last].go[x] = ++size;
			a[size].clr();
		}
		return a[last].go[x];
	}
	void build() {
		l = 1;
		r = 0;
		q[++r] = root;
		a[root].fail = root;
		for (; l <= r; l++) {
			int x = q[l];
			for (int j = 0; j < maxc; j++)
				if (a[x].go[j]) {
					int y = a[x].go[j];
					int last = a[x].fail;
					while (last != root && !a[last].go[j]) last = a[last].fail;
					if (a[last].go[j] && a[last].go[j] != y) a[y].fail = a[last].go[j];
					else a[y].fail = root;
					if (a[a[y].fail].acc) a[y].acc = 1;
					q[++r] = y;
				}
			for (int j = 0; j < maxc; j++)
				if (!a[x].go[j]) {
					if (x != root) a[x].go[j] = a[a[x].fail].go[j];
					else a[x].go[j] = root;
				}
		}
	}
} aca;

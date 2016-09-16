//Link-Cut Tree

//以下为splay元素：
//l, r为左右儿子, p为父亲
//mark为size的增减标记
//change为左右翻转标记
//以下为LCT独有元素
//pre为轻链父亲
//size为树上的子树大小（未验证）
class lctleaf {
  public:
	int l, r, p, pre, size, mark;
	bool change;
};

class LinkCutTree {
  public:
	lctleaf a[100010];
	void make (int x) {
		//更新splay内点x的信息
	}
	void makemark (int x) {
		int lson = a[x].l, rson = a[x].r;
		if (a[x].change) {
			if (lson) {
				a[lson].change = !a[lson].change;
				swap (a[lson].l, a[lson].r);
			}
			if (rson) {
				a[rson].change = !a[rson].change;
				swap (a[rson].l, a[rson].r);
			}
			a[x].change = 0;
		}
		if (a[x].mark) {
			if (lson) {
				a[lson].mark += a[x].mark;
				a[lson].size += a[x].mark;
			}
			if (rson) {
				a[rson].mark += a[x].mark;
				a[rson].size += a[x].mark;
			}
			a[x].mark = 0;
		}
	}
	void clrmark (int x) {
		int ll = 0;
		for (; x; x = a[x].p) qq[++ll] = x;
		for (int i = ll; i; i--) makemark (qq[i]);
	}
	void left (int x) {
		int y = a[x].p, z = a[y].p;
		if (a[z].l == y) a[z].l = x;
		else a[z].r = x;
		a[y].r = a[x].l;
		a[a[x].l].p = y;
		a[x].l = y;
		a[x].p = z;
		a[y].p = x;
		swap (a[y].pre, a[x].pre);
//		make(y);make(x);
	}

	void right (int x) {
		int y = a[x].p, z = a[y].p;
		if (a[z].l == y) a[z].l = x;
		else a[z].r = x;
		a[y].l = a[x].r;
		a[a[x].r].p = y;
		a[x].r = y;
		a[x].p = z;
		a[y].p = x;
		swap (a[y].pre, a[x].pre);
//		make(y);make(x);
	}
	void splay (int x) {
		int y, z;
		clrmark (x);
		while (a[x].p) {
			y = a[x].p;
			z = a[y].p;
			if (z) {
				if (a[z].l == y) {
					if (a[y].l == x) right (y), right (x);
					else left (x), right (x);
				} else {
					if (a[y].l == x) right (x), left (x);
					else left (y), left (x);
				}
			} else if (a[y].l == x) right (x);
			else left (x);
		}
	}

	//查找splay中点x的next
	int next (int x) {
		splay (x);
		makemark (x);
		x = a[x].r;
		do {
			makemark (x);
			if (a[x].l) x = a[x].l;
			else break;
		} while (1);
		return x;
	}

	//变更重链操作
	void access (int x) {
		int p = 0;
		while (x) {
			splay (x);
			a[a[x].r].pre = x;
			a[a[x].r].p = 0;
			a[x].r = p;
			a[p].p = x;
			a[p].pre = 0;
			p = x;
//			make(x);
			x = a[x].pre;
		}
	}

	//将点x置为根，之前的根为root
	//同时更新了size
	void move_root (int root, int x) {
		access (x);
		splay (x);
		a[a[x].l].change = !a[a[x].l].change;
		swap (a[a[x].l].l, a[a[x].l].r);
		a[a[x].l].pre = a[a[x].l].p;
		a[a[x].l].p = 0;
		a[x].l = 0;
		a[root].size -= a[x].size;
		a[x].size += a[root].size;
	}

	//查找点x的根
	int find_root (int x) {
		access (x);
		splay (x);
		while (a[x].l) x = a[x].l;
		splay (x);
		return x;
	}

	//查询lca
	int lca (int x, int y) {
		int root = find_root (x);
		access (x);
		access (y);
		splay (x);
		int xx = x;
		while (a[xx].l) xx = a[xx].l;
		splay (xx);
		if (xx == root) return x;
		else return a[xx].pre;
	}
} lct;

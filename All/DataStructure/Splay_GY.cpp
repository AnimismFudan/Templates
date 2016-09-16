
//splay

//s为子树节点个数
//data为节点权值
//Min为子树权值最小值

class splay {
  public:
	int lson, rson, p, data, Min, s;
} spl[10010];

void make (int x) {
	spl[x].s = 1;
	spl[x].Min = spl[x].data;
	int lson = spl[x].lson, rson = spl[x].rson;
	if (lson) spl[x].s += spl[lson].s, spl[x].Min = min (spl[x].Min, spl[lson].Min);
	if (rson) spl[x].s += spl[rson].s, spl[x].Min = min (spl[x].Min, spl[rson].Min);
}

void Right (int x) {
	int y = spl[x].p, z = spl[y].p;
	if (spl[z].lson == y) spl[z].lson = x;
	else spl[z].rson = x;
	spl[x].p = z;
	spl[y].lson = spl[x].rson;
	spl[spl[y].lson].p = y;
	spl[x].rson = y;
	spl[y].p = x;
	make (y);
	make (x);
}

void Left (int x) {
	int y = spl[x].p, z = spl[y].p;
	if (spl[z].lson == y) spl[z].lson = x;
	else spl[z].rson = x;
	spl[x].p = z;
	spl[y].rson = spl[x].lson;
	spl[spl[y].rson].p = y;
	spl[x].lson = y;
	spl[y].p = x;
	make (y);
	make (x);
}

void splay (int x) {
	int y, z;
	while (spl[x].p) {
		y = spl[x].p;
		z = spl[y].p;
		if (z) {
			if (spl[z].lson == y) {
				if (spl[y].lson == x) Right (y), Right (x);
				else Left (x), Right (x);
			} else {
				if (spl[y].lson == x) Right (x), Left (x);
				else Left (y), Left (x);
			}
		} else if (spl[y].lson == x) Right (x);
		else Left (x);
	}
	root = x;
}

//寻找第num个元素
int finds (int num) {
	if (spl[root].s < num) return 0;
	int x = root;
	int lson;
	for (; x;) {
		lson = spl[x].lson;
		if (num == spl[lson].s + 1) return x;
		if (num <= spl[lson].s) x = lson;
		else num -= spl[lson].s + 1, x = spl[x].rson;
	}
	return 0;
}

//寻找最小值的位置
int findminpos() {
	int x = root;
	int Min = spl[root].Min;
	for (; x;) {
		if (spl[x].data == Min) return x;
		if (spl[spl[x].lson].Min == Min) x = spl[x].lson;
		else x = spl[x].rson;
	}
	return 0;
}


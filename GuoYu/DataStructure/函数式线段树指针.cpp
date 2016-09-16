

class segnode {
  public:
	int s;
	segnode *lson, *rson;
	segnode() : s (0), lson (NULL), rson (NULL) {}
}*root[100010];

segnode* newnode() {
	return new segnode();
}

void Init (segnode *&x, segnode *past, int l, int r, int t) {
	x = newnode();
	if (past != NULL) *x = *past;
	(*x).s += t;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (t <= mid) Init ( (*x).lson, (*x).lson, l, mid, t);
	else Init ( (*x).rson, (*x).rson, mid + 1, r, t);
}
int calc (segnode *x, int l, int r, int ll, int rr) {
	if (x == NULL) return 0;
	if (l == ll && r == rr) {
		return (*x).s;
	}
	int mid = (l + r) >> 1;
	if (rr <= mid) return calc ( (*x).lson, l, mid, ll, rr);
	else if (ll > mid) return calc ( (*x).rson, mid + 1, r, ll, rr);
	else return calc ( (*x).lson, l, mid, ll, mid) + calc ( (*x).rson, mid + 1, r, mid + 1, rr);
}
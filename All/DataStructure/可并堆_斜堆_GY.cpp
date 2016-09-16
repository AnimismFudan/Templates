
class rec {
  public:
	int lson, rson, num;
} heap[1000010];

int merge (int a, int b) {
	if (!a) return b;
	if (!b) return a;
	if (heap[a].num < heap[b].num) swap (a, b);
	heap[a].rson = merge (heap[a].rson, b);
	swap (heap[a].lson, heap[a].rson);
	return a;
}

int Del (int x) {
	return merge (heap[x].lson, heap[x].rson);
}

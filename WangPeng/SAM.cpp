//SAM
struct node {
	node *f,*nex[26];
	int ml,size,first;
	node () { ml = size = first = 0; }
} pool[maxn],*tail, *init, *rank[maxn];
void add(int ch,int len) {
	node *p = tail, *np = &pool[++tot];
	np -> ml = len;
	for (; p && !p -> nex[ch]; p = p -> f) p -> nex[ch] = np;
	tail = np;
	if (!p) np -> f = init;
	else {
		if (p -> nex[ch] -> ml == p -> ml + 1) np -> f = p -> nex[ch];
		else {
			node *q = p -> nex[ch], *just = &pool[++tot];
			*just = *q;
			just -> ml = p -> ml + 1;
			q -> f = np -> f = just;
			for (; p && p -> nex[ch] == q; p = p -> f) p -> nex[ch] = just;
		}
	}
}

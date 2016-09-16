
//id����Ϊ�½�kdtreeʱ��ʹ�õ�Ķ���

class poi {
  public:
	int x, y;
	poi() {}
	poi (int x_, int y_) : x (x_), y (y_) {}
} P[200010], p;

//sx, tx, sy, ty��ʾkdtreeԪ����������������귶Χ
//sΪ������Ԫ�ظ���
//l, rΪ���Ҷ���
class kdleaf {
  public:
	int sx, tx, sy, ty, s;
	int l, r;
} kdt[200010];

//x��y��������
bool cmpx (const int &x, const int &y) {
	return P[x].x < P[y].x;
}
bool cmpy (const int &x, const int &y) {
	return P[x].y < P[y].y;
}

//�õ�y���µ�x������Χ
void renew (int x, int y) {
	if (!y) return;
	kdt[x].sx = min (kdt[x].sx, kdt[y].sx);
	kdt[x].sy = min (kdt[x].sy, kdt[y].sy);
	kdt[x].tx = max (kdt[x].tx, kdt[y].tx);
	kdt[x].ty = max (kdt[x].ty, kdt[y].ty);
}

//����id[]�����ڵ�[l, r]��Χ�½�kdtree�����ظ���ţ���һ������ʽ��stepΪ׼
int kd_build (int l, int r, int step) {
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	nth_element (id + l, id + mid, id + r + 1, step ? cmpx : cmpy);
	int x = id[mid];
	kdt[x].sx = kdt[x].tx = P[x].x;
	kdt[x].sy = kdt[x].ty = P[x].y;
	kdt[x].s = 1;
	kdt[x].l = kd_build (l, mid - 1, !step);
	renew (x, kdt[x].l);
	kdt[x].s += kdt[kdt[x].l].s;
	kdt[x].r = kd_build (mid + 1, r, !step);
	renew (x, kdt[x].r);
	kdt[x].s += kdt[kdt[x].r].s;
	return x;
}

//��������ƽ��ʱʹ�õ��ؽ�����
//ȡ����head�����ж��ӣ����ؽ�kdtree
//��һ������ʽ��step
//�����ؽ���ĸ����
int rebuild (int head, int step) {
	int l, r, x;
	id[l = r = 1] = head;
	for (; l <= r; l++) {
		x = id[l];
		if (kdt[x].l) id[++r] = kdt[x].l;
		if (kdt[x].r) id[++r] = kdt[x].r;
	}
	return kd_build (1, r, step);
}

//����rootΪ���������в���Ԫ��x����һ������ʽΪstep
//�����˲�ƽ��ʱ���������ع�
void Insert (int &root, int x, int step) {
	if (!root) {
		root = x;
		kdt[root].sx = kdt[root].tx = P[x].x;
		kdt[root].sy = kdt[root].ty = P[x].y;
		kdt[root].s = 1;
		return;
	}
	if (step ? cmpx (x, root) : cmpy (x, root) )
		Insert (kdt[root].l, x, !step);
	else Insert (kdt[root].r, x, !step);
	renew (root, x);
	kdt[root].s++;
	if (kdt[kdt[root].l].s > kdt[kdt[root].r].s * 2 + 1
			||	kdt[kdt[root].r].s > kdt[kdt[root].l].s * 2 + 1)
		root = rebuild (root, step);
}

//�����پ���
int dist (poi a, poi b) {
	return abs (a.x - b.x) + abs (a.y - b.y);
}

//�����p��kdtreeԪ��t�������������������پ���
int Min_dist (poi p, kdleaf t) {
	if (p.x < t.sx) {
		if (p.y < t.sy)
			return abs (p.x - t.sx) + abs (p.y - t.sy);
		else if (p.y > t.ty)
			return abs (p.x - t.sx) + abs (p.y - t.ty);
		else
			return abs (p.x - t.sx);
	} else if (t.sx <= p.x && p.x <= t.tx) {
		if (p.y < t.sy)
			return abs (p.y - t.sy);
		else if (p.y > t.ty)
			return abs (p.y - t.ty);
		else
			return 0;
	} else {
		if (p.y < t.sy)
			return abs (p.x - t.tx) + abs (p.y - t.sy);
		else if (p.y > t.ty)
			return abs (p.x - t.tx) + abs (p.y - t.ty);
		else
			return abs (p.x - t.tx);
	}
}

//�����p��kdtreeԪ��t�������������Զ�����پ���
int Max_dist (poi p, kdleaf t) {
	int res = abs (p.x - t.sx) + abs (p.y - t.sy);
	res = max (res, abs (p.x - t.sx) + abs (p.y - t.ty) );
	res = max (res, abs (p.x - t.tx) + abs (p.y - t.sy) );
	res = max (res, abs (p.x - t.tx) + abs (p.y - t.ty) );
	return res;
}

//�����x��kdtree�����е���������
void ask_min (int root, int x, int step, int &ans) {
	if (!root) return;
	ans = min (ans, dist (P[root], P[x]) );
	if (Min_dist (P[x], kdt[root]) >= ans) return;
	if (step ? cmpx (x, root) : cmpy (x, root) ) {
		ask_min (kdt[root].l, x, !step, ans);
		ask_min (kdt[root].r, x, !step, ans);
	} else {
		ask_min (kdt[root].r, x, !step, ans);
		ask_min (kdt[root].l, x, !step, ans);
	}
}

//�����x��kdtree�����е����Զ����
void ask_max (int root, int x, int step, int &ans) {
	if (!root) return;
	ans = max (ans, dist (P[root], P[x]) );
	if (Max_dist (P[x], kdt[root]) <= ans) return;
	if (step ? cmpx (x, root) : cmpy (x, root) ) {
		ask_max (kdt[root].r, x, !step, ans);
		ask_max (kdt[root].l, x, !step, ans);
	} else {
		ask_max (kdt[root].l, x, !step, ans);
		ask_max (kdt[root].r, x, !step, ans);
	}
}

//判断两条线段是否相交
//Attention: 线段和线段的交点在线段的端点上

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct NodeTp {
	int x, y;
	void Read() {
		scanf ("%d%d", &x, &y);
	}
	NodeTp operator- (NodeTp A) {
		return (NodeTp) {
			(x - A.x), (y - A.y)
		};
	}
};

inline int Cross (NodeTp A, NodeTp B) {
	return A.x * B.y - A.y * B.x;
}

bool CheckRec (NodeTp A1, NodeTp A2, NodeTp B1, NodeTp B2) { // 快速跨立实验
	int x1, x2, x3, x4;
	x1 = min (A1.x, A2.x);
	x2 = max (A1.x, A2.x);
	x3 = min (B1.x, B2.x);
	x4 = max (B1.x, B2.x);
	if (x2 < x3 || x4 < x1) return false;
	x1 = min (A1.y, A2.y);
	x2 = max (A1.y, A2.y);
	x3 = min (B1.y, B2.y);
	x4 = max (B1.y, B2.y);
	if (x2 < x3 || x4 < x1) return false;
	return true;
}

bool Check (NodeTp A, NodeTp B, NodeTp C) { // 向量A、B是否在C的两侧
	if (A.x + B.x == 0 && A.y + B.y == 0) return false;
	int tmp1 = Cross (A, C);
	int tmp2 = Cross (B, C);
	if (tmp1 > 0 && tmp2 < 0) return true;
	else if (tmp1 < 0 && tmp2 > 0) return true;
	return false;
}

int main() {
	NodeTp A1, A2, B1, B2;
	A1.Read();
	A2.Read();
	B1.Read();
	B2.Read();
	printf ("Line1: (%d,%d) (%d,%d)\n", A1.x, A1.y, A2.x, A2.y);
	printf ("Line2: (%d,%d) (%d,%d)\n", B1.x, B1.y, B2.x, B2.y);
	if (!CheckRec (A1, A2, B1, B2) ) printf ("Not Cross!\n");
	else if (Check (B1 - A1, B2 - A2, A2 - A1) && Check (A1 - B1, A2 - B1, B2 - B1) ) printf ("Cross!\n");
	else printf ("Not Cross!\n");
	return 0;
}

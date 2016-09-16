#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;
int N;
int a[1010];
void work (int l, int r) {
	int i = l, j = r, m = rand() % (r - l + 1) + l;
	swap (a[m], a[i]);
	m = a[i];
	while (i < j) {
		while (i < j && a[j] >= m) j--;
		if (i < j) a[i] = a[j], i++;
		while (i < j && a[i] <= m) i++;
		if (i < j) a[j] = a[i], j--;
	}
	a[i] = m;
	if (l < i - 1) work (l, i - 1);
	if (i + 1 < r) work (i + 1, r);
}
int main() {
	srand (time (0) );
	freopen ("qs.in", "r", stdin);
	freopen ("qs.out", "w", stdout);
	scanf ("%d", &N);
	for (int i = 1; i <= N; i++) scanf ("%d", &a[i]);
	work (1, N);
	for (int i = 1; i <= N; i++) printf ("%d ", a[i]);
}

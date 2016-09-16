#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MaxN = 307;

int n, m;
int A[MaxN][MaxN], B[MaxN], X[MaxN];

int Suan (char str[]) {
	int s;
	switch (str[0]) {
	case 'M':
		s = 1;
		break;
	case 'W':
		s = 3;
		break;
	case 'F':
		s = 5;
		break;
	case 'T':
		if (str[1] == 'U') s = 2;
		if (str[1] == 'H') s = 4;
		break;
	case 'S':
		if (str[1] == 'A') s = 6;
		if (str[1] == 'U') s = 7;
		break;
	}
	return s;
}

void Init() {
	int i, j, k, t, s1, s2;
	char str1[10], str2[10];
	memset (A, 0, sizeof (A) );
	memset (B, 0, sizeof (B) );
	memset (X, 0, sizeof (X) );
	for (i = 1; i <= m; i++) {
		scanf ("%d %s %s\n", &t, str1, str2);
		for (j = 1; j <= t; j++)
			scanf ("%d", &k), A[i][k]++;
		s1 = Suan (str1);
		s2 = Suan (str2);
		B[i] = (s2 - s1 + 8) % 7;
	}
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) A[i][j] %= 7;
	return;
}

inline void Swap (int &x, int &y) {
	int t = x;
	x = y;
	y = t;
	return;
}

inline int Calc (int a, int b) { //ax=b(mod 7)  x=3/4/5/6/7/8/9
	int x, s;
	for (x = 3, s = a + a - b; x <= 9; x++) {
		s += a;
		if (s % 7 == 0) return x;
	}
	return -1;
}

void Gauss() {
	int i, j, k, p, m1, m2;
	bool flag, fl;
	flag = false;
	for (i = 1, p = 1; i <= m; p++) { //处理第i个方程 消元第p个未知数
		for (j = i + 1, k = i; j <= m; j++)
			if (A[j][p] > A[k][p]) k = j;
		if (A[k][p] != 0) {
			if (k != i) {
				Swap (B[i], B[k]);
				for (j = p; j <= n; j++) Swap (A[i][j], A[k][j]);
			}
			for (j = i + 1; j <= m; j++) {
				m1 = A[i][p];
				m2 = A[j][p];
				fl = true;
				for (k = p; k <= n; k++) {
					A[j][k] = (A[j][k] * m1 - A[i][k] * m2) % 7;
					if (A[j][k] < 0) A[j][k] += 7;
					fl = fl & (A[j][k] == 0);
				}
				B[j] = (B[j] * m1 - B[i] * m2) % 7;
				if (B[j] < 0) B[j] += 7;
				if (fl)
					if (B[j] != 0) {
						printf ("Inconsistent data.\n");
						return;
					} else flag = true;
			}
			i++;
		}
		/*
		for(int i=1;i<=m;i++)
		{
		    for(int j=1;j<=n;j++)
		        cout<<A[i][j]<<' ';
		    cout<<"    "<<B[i]<<endl;
		}
		cout<<endl;
		*/
	}
	if (p < n) {
		printf ("Multiple solutions.\n");
		return;
	}
	if (A[n][n] == 0 && B[n] == 0) {
		printf ("Multiple solutions.\n");
		return;
	}
	X[n] = Calc (A[n][n], B[n]);
	for (i = n - 1; i >= 1; i--) {
		for (j = i + 1, k = 0; j <= n; j++)
			k += A[i][j] * X[j];
		k = B[i] - k;
		k = ( (k % 7) + 7) % 7;
		if (A[i][i] == 0)
			if (k) {
				printf ("Inconsistent data.\n");
				return;
			} else {
				printf ("Multiple solutions.\n");
				return;
			}
		X[i] = Calc (A[i][i], k);
	}
	for (i = 1; i <= n; i++) printf ("%d ", X[i]);
	printf ("\n");
	return;
}

void Solve() {
	int i, j;
	/*
	for(i=1;i<=m;i++)
	{
	    for(j=1;j<=n;j++)
	        cout<<A[i][j]<<' ';
	    cout<<"    "<<B[i]<<endl;
	}
	cout<<endl;
	*/
	Gauss();
	return;
}

int main() {
	freopen ("widget.in", "r", stdin);
	freopen ("widget.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	while (n || m) {
		Init();
		Solve();
		scanf ("%d%d", &n, &m);
	}
	return 0;
}

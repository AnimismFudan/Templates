//Ä£Ê½Æ¥Åä  Knuth_Morris_Pratt(KMP)  Ëã·¨

#include<iostream>
using namespace std;

const int Max_N = 100000;
const int Max_M = 1000;

int n, m;
char s1[Max_N], s2[Max_M];
int next[Max_M];

void GetNext() {
	int i, j;
	next[1] = 0;
	i = 1, j = 0;
	while (i <= m)
		if (j == 0 || s2[i] == s2[j]) {
			i++, j++;
			if (s2[i] == s2[j]) next[i] = next[j];
			else next[i] = j;
		} else j = next[j];
	return;
}

void KMP() {
	int i, j;
	GetNext();
	for (i = 1; i <= n; i++) cout << next[i] << ' ';
	cout << endl;
	i = j = 0;
	while (i <= n && j <= m)
		if (j == 0 || s1[i] == s2[j])
			i++, j++;
		else j = next[j];
	if (j > m) printf ("%d", i - m);
	else printf ("Compare Error!");
	return;
}

int main() {
	freopen ("kmp.in", "r", stdin);
	freopen ("kmp.out", "w", stdout);
	scanf ("%d %d\n", &n, &m);
	scanf ("%s\n", s1 + 1);
	scanf ("%s\n", s2 + 1);
	KMP();
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int A[1 << 20],B[1 << 20],js[1 << 20];
int n,k;

void fwt_xor(int *A, int n) {
	if (n == 1) return;
	fwt_xor(A, n >> 1);
	fwt_xor(A + (n >> 1), n >> 1);
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = 0; i < n >> 1; i++)
		A[i] = js[i] + js[i + (n >> 1)];
	for (int i = (n >> 1); i < n; i++)
		A[i] = js[i - (n >> 1)] - js[i];
	return;
}

void ufwt_xor(int *A, int n) {
	if (n == 1) return;
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = 0; i < n >> 1; i++)
		A[i] = (js[i] + js[i + (n >> 1)]) / 2;
	for (int i = (n >> 1); i < n; i++)
		A[i] = (js[i - (n >> 1)] - js[i]) / 2;
	ufwt_xor(A, n >> 1);
	ufwt_xor(A + (n >> 1), n >> 1);
	return;
}

void fwt_or(int *A, int n) {
	if (n == 1) return;
	fwt_or(A, n >> 1);
	fwt_or(A + (n >> 1), n >> 1);
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = (n >> 1); i < n; i++)
		A[i] = js[i - (n >> 1)] + js[i];
	return;
}

void ufwt_or(int *A, int n) {
	if (n == 1) return;
	ufwt_or(A, n >> 1);
	ufwt_or(A + (n >> 1), n >> 1);
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = (n >> 1); i < n; i++)
		A[i] = js[i] - js[i - (n >> 1)];
	return;
}

void fwt_and(int *A, int n) {
	if (n == 1) return;
	fwt_and(A, n >> 1);
	fwt_and(A + (n >> 1), n >> 1);
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = 0; i < (n >> 1); i++)
		A[i] = js[i + (n >> 1)] + js[i];
	for (int i = (n >> 1); i < n; i++)
		A[i] = js[i];
	return;
}

void ufwt_and(int *A, int n) {
	if (n == 1) return;
	ufwt_and(A, n >> 1);
	ufwt_and(A + (n >> 1), n >> 1);
	for (int i = 0; i < n; i++)
		js[i] = A[i];
	for (int i = 0; i < (n >> 1); i++)
		A[i] = js[i] - js[i + (n >> 1)];		
	return;
}

int main() {
	freopen("fwt.in","r",stdin);
	freopen("fwt.out","w",stdout);
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
		scanf("%d",&A[i]);
	for (int i = 0; i < n; i++)
		scanf("%d",&B[i]);
	int k = 0;
	while ((1 << k) < n) k++;
	
	fwt_and(A, 1 << k);
	fwt_and(B, 1 << k);
	for (int i = 0; i < (1 << k); i++)
		A[i] *= B[i];
	ufwt_and(A, 1 << k);
	for (int i = 0; i < n; i++)
		printf("%d\n",A[i]);
	return 0;
}

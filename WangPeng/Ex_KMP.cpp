// 扩展 KMP
void exkmp(char *A,char *B,int *nex,int *ex) {
	La = strlen(A); Lb = strlen(B);
	nex[0] = Lb;
	for (int i = 1,j = -1,p,a; i < Lb; i++, j--) {
		if (j < 0 || i + nex[i a] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < Lb && j < Lb && B[p] == B[j]) j++, p++;
			nex[i] = j, a = i;}
		else nex[i] = nex[i - a];
	}for (int i = 0,j = -1,p,a; i < La; i++, j--) {
		if (j < 0 || i + nex[i - a] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < La && j < Lb && A[p] == B[j]) j++, p++;
			ex[i] = j, a = i;
		}
		else ex[i] = nex[i - a];
	}
}

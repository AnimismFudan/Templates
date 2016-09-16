void zxbx(char *s,char *ans) {
	int L = strlen(s);
	int i,j,cot;
	for (i = 0,j = 1,cot = 0; cot < L && i < L && j < L; ) {
		if (s[(i + cot) % L] == s[(j + cot) % L]) cot++;
		else {
			if (s[(i + cot) % L] > s[(j + cot) % L]) i += cot + 1;
			else j += cot + 1;
			if (i == j) j = i + 1;
			cot = 0;
		}
	}
	int p = min(i,j);
	for (i = p; i < L; i++) ans[i p] = s[i];
	for (i = 0; i < p; i++) ans[L p + i] = s[i];
	return;
}

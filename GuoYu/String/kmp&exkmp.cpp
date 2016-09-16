
void get_kmp() {
	memset (fail, 0, sizeof (fail) );
	for (int i = 2; i <= N; i++) {
		int x = fail[i - 1];
		while (x && s1[x + 1] != s1[i]) x = fail[x];
		if (s1[x + 1] == s1[i]) fail[i] = x + 1;
		else fail[i] = 0;
	}
	memset (kmp, 0, sizeof (kmp) );
	for (int i = 1; i <= N; i++) {
		int j = kmp[i - 1];
		while (j && s1[j + 1] != s2[i]) j = fail[j];
		if (s1[j + 1] == s2[i]) kmp[i] = j + 1;
		else kmp[i] = 0;
	}
}

void exkmp() {
	memset (fail, 0, sizeof (fail) );
	fail[2] = (s[2] == s[1]);
	int k = 2, r = 1 + fail[2];
	for (int i = 3; i <= len; i++) {
		if (i <= r)
			fail[i] = min (r - i + 1, fail[i - k + 1]);
		while (i + fail[i] <= len && s[fail[i] + 1] == s[i + fail[i]])
			fail[i]++;
		if (i + fail[i] - 1 > r) {
			k = i;
			r = i + fail[i] - 1;
		}
	}
}

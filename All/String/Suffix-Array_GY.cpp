
void getran (int x) {
	tempran[sa[1]] = 1;
	for (int i = 2; i <= N; i++)
		if ( (ran[sa[i]] == ran[sa[i - 1]]) && (ran[sa[i] + x] == ran[sa[i - 1] + x]) )
			tempran[sa[i]] = tempran[sa[i - 1]];
		else tempran[sa[i]] = tempran[sa[i - 1]] + 1;
	memcpy (ran, tempran, sizeof (ran) );
}

void work (int x) {
	memset (temp, 0, sizeof (temp) );
	for (int i = 1; i <= N; i++) temp[ran[i + x]]++;
	for (int i = 1; i < maxn; i++) temp[i] += temp[i - 1];
	for (int i = N; i; i--) tsa[temp[ran[i + x]]--] = i;
	memset (temp, 0, sizeof (temp) );
	for (int i = 1; i <= N; i++) temp[ran[i]]++;
	for (int i = 1; i < maxn; i++) temp[i] += temp[i - 1];
	for (int i = N; i; i--) sa[temp[ran[tsa[i]]]--] = tsa[i];
	getran (x);
}

void getheight() {
	int i, j, k = 0;
	for (i = 1; i <= N; height[ran[i++]] = k)
		for (k ? --k : 0, j = sa[ran[i] - 1]; s[i + k] == s[j + k]; k++);
}

void getST() {
	for (int i = 1; i <= N; i++) ST[0][i] = height[i];
	for (int step = 1, s = 1; (s << 1) <= N; step++, s <<= 1)
		for (int i = 1; i <= N; i++)
			if (i + s <= N) ST[step][i] = min (ST[step - 1][i], ST[step - 1][i + s]);
			else ST[step][i] = 0;
}

//原串中x、y位置的后缀的lcp
int lcp (int x, int y) {
	if (x == y) return N - x + 1;
	int l = ran[x], r = ran[y];
	if (l > r) swap (l, r);
	l++;
	int delta = r - l + 1;
	int t = log (delta) / log (2);
	return min (ST[t][l], ST[t][r - (1 << t) + 1]);
}

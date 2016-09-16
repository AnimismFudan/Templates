
void manachar() {
	memset (length, 0, sizeof (length) );
	length[1] = 1;
	int k = 1, rr = k + length[k] - 1;
	for (int i = 2; i <= r; i++) {
		if (i <= rr) length[i] = min (rr - i + 1, length[2 * k - i]);
		while (i + length[i] <= r && i - length[i] > 0 && ss[i + length[i]] == ss[i - length[i]]) length[i]++;
		if (rr < i + length[i] - 1) {
			k = i;
			rr = i + length[i] - 1;
		}
	}
}

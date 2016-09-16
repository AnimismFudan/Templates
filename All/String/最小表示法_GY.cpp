
//先倍长字符串
//字符串s2长度为M
//返回从第i个字符开始时s2为最小表示
int Minnote() {
	int i = 1, j = 2, k = 0;
	for (; k <= M && i <= M && j <= M;) {
		if (i == j) j++;
		if (s2[i + k] == s2[j + k]) k++;
		else {
			if (s2[i + k] > s2[j + k]) i = i + k + 1;
			else j = j + k + 1;
			k = 0;
		}
	}
	return i;
}

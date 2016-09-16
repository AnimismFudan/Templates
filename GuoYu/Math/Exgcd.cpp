
LL exgcd (LL a, LL b, LL &x, LL &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	LL r = exgcd (b, a % b, x, y);
	LL t = x;
	x = y;
	y = t - a / b * y;
	return r;
}

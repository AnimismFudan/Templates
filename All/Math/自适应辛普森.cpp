
double eps = 1e-6;

double f (double x) {
	//数学函数
}

double Simpson (double a, double b) {
	double c = (a + b) / 2;
	return (f (a) + 4 * f (c) + f (b) ) / 6 * (b - a);
}
double AdaptiveSimpson (double a, double b, double eps) {
	double c = (a + b) / 2;
	double S = Simpson (a, b);
	double S1 = Simpson (a, c);
	double S2 = Simpson (c, b);
	if (fabs (S1 + S2 - S) < 15 * eps) return S;
	else return AdaptiveSimpson (a, c, eps / 2) + AdaptiveSimpson (c, b, eps / 2);
}

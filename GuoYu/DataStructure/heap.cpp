//二叉堆

//henu[N] 表示堆内位置为x的元素存储的信息（或对应外部元素的序号）
//nuhe[N] 表示外部元素对应堆内元素的位置
//henu[N] 与 nuhe[N] 互逆， 模板未将nuhe[N]写入

//堆内位置为x的元素的上下调整
void updn(int x){
	for (; x > 1 && henu[x] < henu[x>>1]; x >>= 1)
		swap(henu[x>>1],henu[x]);
	int xx = x << 1;
	while (xx <= last){
		if (xx < last && henu[xx] > henu[xx ^ 1])
			xx = xx ^ 1;
		if (henu[x] > henu[xx]){
			swap(henu[x], henu[xx]);
			x = xx;
			xx = x << 1;
		}else break;
	}
}

//弹出堆顶元素
LL pop(){
	LL res = henu[1];
	swap(henu[1], henu[last]);
	henu[last--]=0;
	if (last)
		updn(1);
	return res;
}

//压入元素x
void push(LL x){
	++last;
	henu[last]=x;
	updn(last);
}
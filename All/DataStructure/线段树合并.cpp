merge(a,b):
	如果a,b中有一个不含任何元素，就返回另一个
	如果a,b都是叶子，返回merge_leaf(a,b)
	返回merge(a->l,b->l)与merge(a->r,b->r)连接成的树

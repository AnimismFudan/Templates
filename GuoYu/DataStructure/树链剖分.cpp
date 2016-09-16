//树链剖分

//TreeSize[N] 点x的子树大小
//Depth[N] 点x的深度
//HeavyChild[N] 点x的重儿子
//Block[N] 点x所在的链标号，同时也是该链的最高点的序号
//NodeID[N] 点x在序列中的位置
//IndexToNode[N] 序列中第x个点的序号
//BlockLeft[N] 编号为x的链在序列中的左端点的位置（链的最高点）
//BlockRight[N] 编号为x的链在序列中的右端点的位置（链的最低点）
//可以将所有点建立一棵线段树
//得出的序列保证了每条轻重链连续
//并保证了每个点的子树内除其所在重链外所有点都连续

//预处理每个点的基本信息
void dfs_size(int x){
	TreeSize[x] = 1;
	for(int i = st[x]; i; i = ne[i]){
		int y = go[i];
		if(y == fa[x]) continue;
		fa[y] = x;
		Depth[y] = Depth[x]+1;
		dfs_size(y);
		TreeSize[x] += TreeSize[y];
		if(TreeSize[HeavyChild[x]] < TreeSize[y])
			HeavyChild[x] = y;
	}
}

//轻重链剖分
void dfs_lh(int x, int block) {
	Block[x] = block;
	NodeID[x] = ++idx;
	IndexToNode[idx] = x;
	if (!BlockLeft[block])
		BlockLeft[block]=idx;
	BlockRight[block]=idx;
	if (HeavyChild[x])
		dfs_lh(HeavyChild[x],block);
	for(int i=st[x];i;i=ne[i]) {
		int y=go[i];
		if(y == fa[x] || y == HeavyChild[x])
			continue;
		dfs_lh(y,y);
	}
}

//主进程
void Decomposition(int s, int N) {
	idx = 0;
	fa[s] = 0;
	memset(HeavyChild,0,sizeof(HeavyChild));
	dfs_size(s);
	dfs_lh(s,s);
}

//（x，y）的lca
int lca(int x, int y){
	while (Block[x] != Block[y]){
		if (Depth[Block[x]] < Depth[Block[y]])
			swap(x,y);
		x = fa[Block[x]];
	}
	if (Depth[x] < Depth[y])return x;
	else	return y;
}

LL **f=new LL *[W+1];
for (int w=0;w<=W;w++)
	f[w]=new LL[M+1];

LL ***ff=new LL **[W+1];
for (int w=0;w<=W;w++){
	ff[w]=new LL *[M+1];
	for (int m=0;m<=M;m++)
		ff[w][m]=new LL [SS+1]; 
}

for (int w=0;w<=W;w++)
	delete [] f[w];
delete [] f;

for (int w=0;w<=W;w++){
	for (int m=0;m<=M;m++){
		delete [] ff[w][m];
	}
	delete [] ff[w];
}
delete [] ff;
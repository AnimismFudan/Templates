const int step[8]={1,10,100,1000,10000,100000,1000000,10000000};
const int con=100000000;
class gj{
	public:
	int a[110];
	void getdata(const int &x){memset(a,0,sizeof(a));a[0]=1;a[1]=x;}
	void getlarge(char s[]){
		memset(a,0,sizeof(a));
		int len=strlen(s);
		a[0]=(len-1)/8+1;
		for (int i=0;i<a[0];i++)
			for (int j=0;j<8;j++)
				if (len>i*8+j)
				a[i+1]+=(s[len-i*8-j-1]-'0')*step[j];
	}
	void priln(){
		printf("%d",a[a[0]]);
		for (int i=a[0]-1;i>0;i--)printf("%08d",a[i]);
		printf("\n");
	}
	bool operator <(const gj &X){
		if (a[0]<X.a[0])return true;if (a[0]>X.a[0])return false;
		for (int i=a[0];i;i--){if (a[i]<X.a[i])return true;if (a[i]>X.a[i])return false;}
		return false;
	}
	bool operator >(const gj &X){
		if (a[0]<X.a[0])return false;if (a[0]>X.a[0])return true;
		for (int i=a[0];i;i--){if (a[i]<X.a[i])return false;if (a[i]>X.a[i])return true;}
		return false;
	}
	bool operator <=(const gj &X){
		if (a[0]<X.a[0])return true;if (a[0]>X.a[0])return false;
		for (int i=a[0];i;i--){if (a[i]<X.a[i])return true;if (a[i]>X.a[i])return false;}
		return true;
	}
	bool operator >=(const gj &X){
		if (a[0]<X.a[0])return false;if (a[0]>X.a[0])return true;
		for (int i=a[0];i;i--){if (a[i]<X.a[i])return false;if (a[i]>X.a[i])return true;}
		return true;
	}
	bool operator ==(const gj &X){
		if (a[0]!=X.a[0])return false;for (int i=a[0];i;i--)if (a[i]!=X.a[i])return false;
		return true;
	}
	gj operator + (const gj &X){
		gj c;memset(c.a,0,sizeof(c.a));
		for (int i=1;i<=a[0]||i<=X.a[0];i++){
			c.a[i]+=a[i]+X.a[i];
			c.a[i+1]=c.a[i]/con;
			c.a[i]=c.a[i]-c.a[i+1]*con;
		}
		if (a[0]<X.a[0])c.a[0]=X.a[0];else c.a[0]=a[0];
		while (c.a[c.a[0]+1])++c.a[0];
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator +(const int &X){
		gj c;memcpy(c.a,a,sizeof(c.a));c.a[1]+=X;
		for (int i=1;i<=c.a[0]&&c.a[i]>=con;i++)c.a[i]-=con,c.a[i+1]++;
		while (c.a[c.a[0]+1])c.a[0]++;
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator -(const gj &X){
		gj c;memcpy(c.a,a,sizeof(c.a));
		for (int i=1;i<=a[0];i++){c.a[i]=c.a[i]-X.a[i];if (c.a[i]<0){c.a[i+1]--;c.a[i]+=con;}}
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator -(const int &X){
		gj c;memcpy(c.a,a,sizeof(c.a));
		c.a[1]-=X;
		for (int i=1;c.a[i]<0;i++)c.a[i+1]--,c.a[i]+=con;
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator * (const gj &X){
		gj c;memset(c.a,0,sizeof(c.a));
		int t;LL x;
		for (int i=1;i<=a[0];i++)
			for (int j=1;j<=X.a[0];j++){
				x=(LL)a[i]*X.a[j]+c.a[i+j-1];
				t=x/con;
				c.a[i+j]+=t;
				c.a[i+j-1]=x-t*con;
			}
		c.a[0]=max(a[0]+X.a[0]-1,0);
		while (c.a[c.a[0]+1])c.a[0]++;
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator *(const int &X){
		gj c;memset(c.a,0,sizeof(c.a));
		int t;LL x;
		for (int i=1;i<=a[0];i++){
			x=(LL)a[i]*X+c.a[i];
			t=x/con;
			c.a[i+1]+=t;
			c.a[i]=x-t*con;
		}
		c.a[0]=a[0];if (c.a[c.a[0]+1]>0)c.a[0]++;
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator /(const int &X){
		gj c;memcpy(c.a,a,sizeof(c.a));
		LL rem=0,s=0;
		for (int i=c.a[0];i;i--){
			s=rem*con+c.a[i];
			c.a[i]=s/X;
			rem=s-(LL)c.a[i]*X;
		}
		while (c.a[0]&&!c.a[c.a[0]])c.a[0]--;
		return c;
	}
	gj operator %(gj X){
		if ((*this)<X)return *this;
		gj c;c.getdata(0);
		gj d;d.getdata(0);
		c.a[0]=a[0]-X.a[0]+1;
		d.a[0]=X.a[0]-1;
		for (int i=1;i<X.a[0];i++)d.a[i]=a[a[0]-X.a[0]+i+1];
		for (int i=a[0]-X.a[0]+1;i>0;i--){
			for (int j=d.a[0];j;j--)d.a[j+1]=d.a[j];
			d.a[1]=a[i];
			d.a[0]++;
			while (d.a[0]&&!d.a[d.a[0]])d.a[0]--;
			int ll=0,rr=con-1;
			while (ll<rr){
				int mid=(ll+rr+1)>>1;
				if (d>=(X*mid))ll=mid;
				else rr=mid-1;
			}
			c.a[i]=ll;
			d=d-X*ll;
		}
		return d;
	}
}A,B,C;
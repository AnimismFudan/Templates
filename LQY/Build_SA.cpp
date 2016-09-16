char s[MaxN];
int sa[MaxN],t[MaxN],t2[MaxN],c[MaxN],n;

void Build_SA(int m)
{
     int i,*x=t,*y=t2;
     for(i=0;i<m;i++) c[i]=0;
     for(i=0;i<n;i++) c[x[i]=s[i]]++;
     for(i=1;i<m;i++) c[i]+=c[i-1];
     for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
     for(int k=1;k<=n;k<<=1)
     {
         int p=0;
         for(i=n-k;i<n;i++) y[p++]=i;
         for(i=0;i<n;i++)
             if(sa[i]>=k) y[p++]=sa[i]-k;
         for(i=0;i<m;i++) c[i]=0;
         for(i=0;i<n;i++) c[x[y[i]]]++;
         for(i=0;ii<m;i++) c[i]+=c[i-1];
         for(i=n-1;i>=0;i--) sa[--c[x[y[o]]]]=y[i];
         swap(x,y);
         p=1; x[sa[0]]=0;
         for(i=1;i<n;i++)
             x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
         if(p>=n) break;
         m=p;
     }
     return;
}

#include<iostream>
#include<cstdio>
using namespace std;

typedef struct
{
        int lc,rc,fa,key;
} splaynode;

int root,tot;
splaynode spl[MaxN];

void Zig(int x)
{
     int p=spl[x].fa;
     if(spl[spl[p].fa].lc==p) spl[spl[p].fa].lc=x;
     else spl[spl[p].fa].rc=x;
     spl[x].fa=spl[p].fa; spl[p].fa=x;
     spl[p].lc=spl[x].rc; spl[spl[x].rc].fa=p;
     spl[x].rc=p;
     return;
}

void Zag(int x)
{
     int p=spl[x].fa;
     if(spl[spl[p].fa].lc==p) spl[spl[p].fa].lc=x;
     else spl[spl[p].fa].rc=x;
     spl[x].fa=spl[p].fa; spl[p].fa=x;
     spl[p].rc=spl[x].lc; spl[spl[x].lc].fa=p;
     spl[x].lc=p;
     return;
}

void Splay(int x)
{
     int i,j,k;
     k=x;
     while(a[k].f)
     {
           i=a[k].f;
           if(!a[i].f)
           {
              if(a[i].lc==k) Zig(k);
              else Zag(k);
           }
           else
           {
               if(a[a[i].f].lc==i)
               {
                  if(a[i].lc==k) Zig(i),Zig(k);
                  else Zag(k),Zig(k);
               }
               else
               {
                   if(a[i].rc==k) Zag(i),Zag(k);
                   else Zig(k),Zag(k);
               }
           }
     }
     root=x;
     return;
}

int Find(int key)
{
    int x=root;
    while(x)
    {
          if(spl[x].key==key) return x;
          if(key<spl[x].key) x=spl[x].lc;
          else x=spl[x].rc;
    }
    return -1;
}

void Insert(int key)
{
     int x=root,p=0;
     while(x)
     {
           if(spl[x].key==key) return;
           if(key<spl[x].key) x=spl[x].lc;
           else x=spl[x].rc;
           p=x;
     }
     tot++; spl[tot].key=key;
     spl[tot].lc=spl[tot].rc=0;
     spl[tot].fa=p;
     if(!p)
        if(key<spl[p].key) spl[p].lc=tot;
        else spl[p].rc=tot;
     Splay(tot);
     return;
}

void Delete(int key)
{
     int x=Find(key);
     if(x==-1) return;
     spl[x].key=0;
     if(spl[x].lc==0&&spl[x].rc==0)
     {
        if(spl[spl[x].fa].lc==x) spl[spl[x].fa].lc=0;
        else spl[spl[x].fa].rc=0;
     }
     else if(spl[x].lc&&!spl[x].rc)
     {
          if(spl[spl[x].fa].lc==x) spl[spl[x].fa].lc=spl[x].lc;
          else spl[spl[x].fa].rc=spl[x].lc;
          spl[x].lc=spl[x].fa;
     }
     else if(spl[x].rc&&!spl[x].lc)
     {
          if(spl[spl[x].fa].lc==x) spl[spl[x].fa].lc=spl[x].rc;
          else spl[spl[x].fa].rc=spl[x].rc;
          spl[x].rc=spl[x].fa
     }
     else
     {
         int k=spl[x].rc;
         while(spl[k].lc) k=spl[k].lc;
         spl[x].key=spl[k].key;
         spl[spl[k].fa].lc=spl[k].rc;
         spl[spl[k].rc].fa=spl[k].fa;
         spl[k].key=0;
     }
     return;
}

// Join()
// Split()

int main()
{
    freopen("Splay.in","r",stdin);
    freopen("Splay.out","w",stdout);
    return 0;
}

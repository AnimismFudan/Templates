#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

const int MaxN=100007;

typedef struct treapnode
{
        treapnode *lc,*rc;
        int key,pro;
} treapnode,*treap;

typedef struct {int a,b;} node;

treap null,root;
int n,m,delt; long long s;
node sh[MaxN],gr[MaxN];

int Cmp(const void *a,const void *b)
{
    return (*(node*)b).b-(*(node*)a).b;
}

void Init()
{
     scanf("%d%d",&n,&m);
     for(int i=1;i<=n;i++)
         scanf("%d%d",&sh[i].a,&sh[i].b);
     qsort(sh+1,n,sizeof(node),Cmp);
     for(int i=1;i<=m;i++)
         scanf("%d%d",&gr[i].a,&gr[i].b);
     qsort(gr+1,m,sizeof(node),Cmp);
     
     srand(time(0));
     null=new treapnode;
     null->lc=null; null->rc=null;
     root=null;
     return;
}

void Right_Rotate(treap &p)
{
     treap q;
     q=p->lc;
     p->lc=q->rc;
     q->rc=p;
     p=q;
     return;
}

void Left_Rotate(treap &p)
{
     treap q;
     q=p->rc;
     p->rc=q->lc;
     q->lc=p;
     p=q;
     return;
}

void Insert(treap &x,int key)
{
     if(x==null)
     {
        x=new treapnode;
        x->lc=null; x->rc=null;
        x->key=key; x->pro=rand();
        return;
     }
     if(key<=x->key)
     {
        Insert(x->lc,key);
        if(x->lc->pro<x->pro)
           Right_Rotate(x);
     }
     else
     {
         Insert(x->rc,key);
         if(x->rc->pro<x->pro)
            Left_Rotate(x);
     }
     return;
}

void Search(treap &x,int key)
{
     if(x==null) return;
     if(key<=x->key)
     {
        delt=x->key;
        Search(x->lc,key);
     }
     else Search(x->rc,key);
     return;
}

void Delete(treap &x,int key)
{
     if(x==null) return;
     if(key<x->key) Delete(x->lc,key);
     else if(key>x->key) Delete(x->rc,key);
     else
     {
         if(x->rc==null&&x->lc==null)
         { delete x; x=null; }
         else if(x->rc==null)
              {
                 treap tt;
                 tt=x; x=x->lc;
                 delete tt;
              }
         else if(x->lc==null)
              {
                 treap tt;
                 tt=x; x=x->rc;
                 delete tt;
              }
         else if(x->lc->pro<x->rc->pro)
              {
                 Right_Rotate(x);
                 Delete(x->rc,key);
              }
         else
         {
             Left_Rotate(x);
             Delete(x->lc,key);
         }
     }
     return;
}

void Solve()
{
     int i,j;
     //for(i=1;i<=n;i++)
     //    cout<<sh[i].a<<' '<<sh[i].b<<endl;
     //cout<<endl;
     //for(i=1;i<=m;i++)
     //    cout<<gr[i].a<<' '<<gr[i].b<<endl;
     //cout<<endl;
     i=1; j=1;
     while(i<=n)
     {
           while(j<=m&&gr[j].b>=sh[i].b)
                 Insert(root,gr[j].a),j++;
           delt=-1;
           Search(root,sh[i].a);
           if(delt==-1) {printf("-1");return;}
           s+=delt;
           Delete(root,delt);
           i++;
     }
     cout<<s;
     return;
}

int main()
{
    freopen("gourmet.in","r",stdin);
    freopen("gourmet.out","w",stdout);
    Init();
    Solve();
    return 0;
}

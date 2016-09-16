//倍增LCA 

void GetD(int id,int de) //更新深度
{
     int i;
     d[id]=de; vis[id]=true;
     for(i=0;i<iv[id].size();i++)
         if(!vis[iv[id][i]])
         {
            f[iv[id][i]][0]=id;
            GetD(iv[id][i],de+1);
         }
     return;
}

void GetF() //更新f[i][j]值 
{
     int i,j;
     for(j=1;(1<<j)<=n;j++)
         for(i=1;i<=n;i++)
             if(f[i][j-1]!=0)
                f[i][j]=f[f[i][j-1]][j-1]; // 第i个节点的2^j祖先就是第i个节点的2^(j-1)祖先的2^(j-1)祖先 
     return;
}

int LCA(int a,int b)
{
    int i,j;
    if(d[a]>d[b]) j=a,a=b,b=j;
    i=(int)(log(1.0*(dep[u]-dep[v]))/log(2.0))+1;
    for(j=i;j>=0&&d[a]!=d[b];j--) //调整a、b深度相同 
        if((1<<j)<=d[b]-d[a]) b=f[b][j];
    if(a==b) return a;
    i=(int)(log(1.0*dep[u])/log(2.0))+1;
    for(j=i;j>=0;j--) //同时向上找祖先 
        if(f[a][j]!=0&&f[a][j]!=f[b][j]) //只要存在该祖先并且祖先不相同 则同时向上 
           a=f[a][j],b=f[b][j];
    return f[a][0]; //最近公共祖先 
}

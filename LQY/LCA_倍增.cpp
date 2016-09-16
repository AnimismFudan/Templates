//����LCA 

void GetD(int id,int de) //�������
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

void GetF() //����f[i][j]ֵ 
{
     int i,j;
     for(j=1;(1<<j)<=n;j++)
         for(i=1;i<=n;i++)
             if(f[i][j-1]!=0)
                f[i][j]=f[f[i][j-1]][j-1]; // ��i���ڵ��2^j���Ⱦ��ǵ�i���ڵ��2^(j-1)���ȵ�2^(j-1)���� 
     return;
}

int LCA(int a,int b)
{
    int i,j;
    if(d[a]>d[b]) j=a,a=b,b=j;
    i=(int)(log(1.0*(dep[u]-dep[v]))/log(2.0))+1;
    for(j=i;j>=0&&d[a]!=d[b];j--) //����a��b�����ͬ 
        if((1<<j)<=d[b]-d[a]) b=f[b][j];
    if(a==b) return a;
    i=(int)(log(1.0*dep[u])/log(2.0))+1;
    for(j=i;j>=0;j--) //ͬʱ���������� 
        if(f[a][j]!=0&&f[a][j]!=f[b][j]) //ֻҪ���ڸ����Ȳ������Ȳ���ͬ ��ͬʱ���� 
           a=f[a][j],b=f[b][j];
    return f[a][0]; //����������� 
}

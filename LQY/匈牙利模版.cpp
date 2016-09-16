#include  <iostream> 
#include  <fstream>  
using   namespace  std;
const   int  MAXN  =   100 ;
int  uN, vN;   // u,v数目  
bool  g[MAXN][MAXN]; // g[i][j] 表示 xi与yj相连  
int  xM[MAXN], yM[MAXN];  //  输出量  
bool  chk[MAXN];  // 辅助量 检查某轮 y[v]是否被check   
 
bool  SearchPath( int  u )
  {
     int  v;
     for(v = 0; v < vN; v ++ )
      {
         if(g[u][v] && ! chk[v])
          {
            chk[v] = true ;
             if  (yM[v]== -1 || SearchPath(yM[v])) 
              {
                yM[v] = u;
                xM[u] = v;
                return  true ;
             } 
          } 
      } 
     return  false ;
  } 
 
int  MaxMatch()
  {
    int  u;
    int  ret  =   0 ;
    memset(xM,  -1 ,  sizeof (xM));
    memset(yM,  -1 ,  sizeof (yM));
    for(u = 0 ; u < uN; u ++ )
      {
         if (xM[u] == - 1 )
          {
             memset(chk, false , sizeof (chk));
             if(SearchPath(u)) ret++ ;
        } 
    } 
     return  ret;
} 
 
int  main(void)
  {
     int  i, k; 
     int  tU, tV;
    ifstream cin("test.in");
    ofstream cout("test.out");
    cin  >>  uN  >>  vN  >>  k;
    memset(g,  false ,  sizeof (g));
     for  (i = 0 ; i < k; i ++ )
      {
        cin >> tU >> tV;
        g[tU][tV]=true ;
    }  
     int  M = MaxMatch();
    cout  <<" Total Match:  " << M <<endl;
     for  (i = 0 ; i < MAXN; i ++ )
         if  (xM[i]  !=   - 1 )
            cout<<i<<' '<<xM[i]<<endl;   
     return   0 ; 
}  


 /**/ /* **********
test data:
    3 3 3
    1 1
    1 0
    2 2
********** */ 

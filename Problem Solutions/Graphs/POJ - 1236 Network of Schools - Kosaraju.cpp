
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;

const int N = 1e4+10 , M = 1e6+10 ;
int n ;

struct ADJ{
    int head[N] , nxt[M] , to[M] , ne ;

    void addEdge(int f, int t ) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }

    void init(int n) {
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

}adj , radj , Cgraph ;

int vis[N] , vid , stk[N] , stkSz , compId[N] , ncp ;

void dfs1( int u ){
    vis[u] = vid ;
  
    for ( int e = adj.head[u] ; ~e ; e = adj.nxt[e] ){
        int v = adj.to[e] ;
        if ( vis[v] == vid )
            continue ;
        dfs1(v) ;
    }
    stk[stkSz++] = u ;
}

void dfs2 ( int u , int cid ){
    compId[u] = cid ;
    vis[u] = vid ;
  
    for ( int e = radj.head[u] ; ~e ; e = radj.nxt[e] ){
        int v = radj.to[e] ;
        if ( vis[v] == vid )
            continue ;
        dfs2 ( v , cid ) ;
    }
}

int notSrc[N] , notSnk[N] ;

void Kosaraju ( ){
    ++vid ;
    for ( int i = 0 ; i < n ; i++ )
        if ( vis[i] != vid )
            dfs1(i) ;

    vid ++ ;
    ncp = 0 ;
    for ( int i = n-1 ; ~i ; i-- )
       if ( vis[stk[i]] != vid )
            dfs2 ( stk[i] , ncp++ );

    Cgraph.init(ncp) ;
    for ( int u = 0 ; u < n ; u ++ ){
        for ( int e = adj.head[u] ; ~e ; e = adj.nxt[e] ){
            int v = adj.to[e] ;
            if ( compId[v] == compId[u] )
                continue ;
            Cgraph.addEdge(compId[u] , compId[v] ) ;
            notSnk[ compId[u] ] = vid ;
            notSrc[ compId[v] ] = vid ;
        }
    }
}
int m , q ;

int main () {

    scanf ( "%d" , &n ) ;
    adj.init(n) ;
    radj.init(n) ;
    for ( int i = 0 ; i < n ; i++ ){
        int x ;
        while ( scanf("%d",&x) , x ){
            --x ;
            adj.addEdge(i,x) ;
            radj.addEdge(x,i) ;
        }
    }
    Kosaraju() ;
    int cntSrc = 0 , cntSnk = 0 ;
    for ( int i = 0 ; i < ncp ; i++ )
        cntSrc += (notSrc[i] != vid) , cntSnk += (notSnk[i] != vid) ;
    printf( "%d\n%d\n" , cntSrc , ncp == 1 ? 0 : max ( cntSrc , cntSnk ) ) ;
    return 0 ;
}

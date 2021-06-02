// https://www.spoj.com/problems/TOPOSORT/en/
// Topological Sorting

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10 , M = 1e6+10 ;

int head[N], nxt[M], to[M], ne , n , vid , m ,u,v , Indeg[N] , res[N] , resSz;


void addEdge(int f, int t ) {
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
    Indeg[t]++ ;
}
void init(int n) {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}
void topo(){
    priority_queue <int> pq ;
    for ( int i = 0 ;i < n ;i ++ )
        if( !Indeg[i] )
            pq.push(-i) ;

    while ( !pq.empty() ){
        int u = -pq.top() ;
        pq.pop() ;
        res[resSz++] = u;
        for ( int e = head[u] ; ~e ; e = nxt[e] ){
            int v = to[e] ;
            if ( !--Indeg[v] )
                pq.push(-v) ;
        }
    }

}

int main()
{
    scanf( "%d%d", &n , &m ) ;
    init(n) ;
    for ( int i = 0 ; i < m ; i ++ ){
        scanf( "%d%d" , &u , &v );
        u-- , v-- ;
        addEdge(u,v) ;
    }
    topo() ;
    if ( resSz != n ){
        puts ( "Sandro fails.\n") ;
        return 0 ;
    }
    for ( int i = 0 ;i < n ; i ++ )
        printf ( "%d%c" , res[i]+1 , " \n"[i==n-1] ) ;
    return 0 ;
}

// https://v...content-available-to-author-only...e.net/problem/EOlymp-1453
// bellman ford algorithm

#include <cstdio>
#include<queue>
#include<cstring>


using namespace std;

const int N = 1e3 + 10 , M = 1e4+10 ;

int head[N], nxt[M], to[M], ne , cost[M] , dis[M] , n , vid , inque[N] ;


void addEdge(int f, int t, int cst ) {
    nxt[ne] = head[f];
    to[ne] = t;
    cost[ne] = cst ;
    head[f] = ne++;
}
void addBiEdge( int f , int t , int cst ){
    addEdge(f,t,cst) ;
    addEdge(t,f,cst) ;
}
void init(int n) {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}

bool bellman( int src ){
    queue<int> q ;
     memset ( dis , 0x3f , sizeof (dis[0])*n ) ;
    dis[src] = 0 ;
    inque[src] = ++vid ;
    int cnt = n ;
    q.push(src) ;
    while ( cnt-- && q.size()){
        int s = q.size() ;
        while ( s-- ){
            int u = q.front() ;
            q.pop() ;
            inque[u] = 0 ;
            for ( int e = head[u] ; ~e ; e = nxt[e] ){
                int v = to[e] ;
                int d = dis[u] + cost[e] ;
                if ( dis[v] > d ){
                    if ( !cnt ){
                        return false ;
                    }
                    dis[v] = d ;
                    if ( inque[v] != vid ){
                        inque[v] = vid ;
                        q.push(v) ;

                    }

                }
            }
        }
    }
    return true ;

}

void ShortestPath ( int src ){
    memset ( dis , 0x3f , sizeof (dis[0])*n ) ;
    dis[src] = 0 ;
    priority_queue <pair<int,int>> pq ;
    pq.push(make_pair(0,src)) ;
    while ( pq.size() ){
        int u , d ;
        d = -pq.top().first ;
        u = pq.top().second ;

        pq.pop() ;
        if ( d != dis[u] )
            continue ;
        for ( int e = head[u] ; ~e ; e = nxt[e] ){
            int v = to[e] ;
            if ( dis[v] > d + cost[e] ){
                dis[v] = d + cost[e] ;
                pq.push( make_pair(-dis[v] , v) ) ;
            }
        }

    }

}
int main()
{

    int m;
    scanf("%d%d",&n,&m);

    init(n) ;
    while(m--){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        u--,v--;
        addEdge(u,v,c) ;
    }
    bellman( 0 );
    for ( int i = 0 ; i < n ; i ++ ){
        if ( dis[i] == 0x3f3f3f3f )
            printf ( "%d%c" , 30000 , " \n"[i==n-1] ) ;

        else
            printf( "%d%c" , dis[i] , " \n"[i==n-1]  ) ;

    }

}

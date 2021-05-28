
#include <cstdio>
#include<queue>
#include<cstring>


using namespace std;

const int N = 1e3 + 10 , M = 4 * N ;

int head[N], nxt[M], to[M], ne , cost[M] , dis[M] , n ;


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


//    #ifdef LOCAL
//        freopen("input.txt", "r", stdin);
//        freopen("output.txt", "w", stdout);
//    #endif // LOCAL
    int m;
    scanf("%d%d",&m,&n);

    init(n) ;
    while(m--){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        u--,v--;
        addBiEdge(u,v,c) ;
    }
    ShortestPath(n-1);
    printf("%d\n",dis[0]);

}

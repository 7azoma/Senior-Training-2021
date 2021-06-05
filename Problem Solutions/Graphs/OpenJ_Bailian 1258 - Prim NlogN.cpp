/*
	Agri-Net OpenJ_Bailian - 1258 
	Prim - NlogN
 */
#include <cstdio>
#include<queue>
#include<cstring>


using namespace std;

const int N = 1e2 + 10 , M = N * N ;

int vis[N] ,vid=0,head[N], nxt[M], to[M], ne , cost[M] , dis[M] , n ;


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

int prim ( int src ){
    vid++;
    memset ( dis , 0x3f , sizeof (dis[0])*n ) ;
    dis[src] = 0 ;
    priority_queue <pair<int,int>> pq ;
    pq.push(make_pair(0,src)) ;
    int res=0;
    while ( pq.size() ){
        int u , d ;
        d = -pq.top().first ;
        u = pq.top().second ;

        pq.pop() ;
        if ( vis[u]==vid )
            continue ;
        vis[u]=vid;
        res+=d;
        for ( int e = head[u] ; ~e ; e = nxt[e] ){
            int v = to[e] ;
            if ( dis[v] > cost[e]  ){
                dis[v] = cost[e] ;
                pq.push( make_pair(-dis[v] , v) ) ;
            }
        }

    }
    return res;

}
int main()
{
//        freopen("agrinet.in","r",stdin);
//    freopen("agrinet.out","w",stdout);

    while(~scanf("%d",&n)){
        init(n);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                int v;
                scanf("%d",&v);
                addEdge(i,j,v);
            }

        printf("%d\n", prim(0));
    }
    return 0;

}

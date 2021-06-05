/*
	Agri-Net OpenJ_Bailian - 1258 
	kruskal
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10 , M = N * N ;

int vis[N] ,vid=0,head[N], nxt[M], to[M], ne , cost[M] , dis[M] , n ;

struct DSU
{
    int par[N], sz[N], sets[N], pos[N], tail[N], nxt[N], cnt;
    void init(int n)
    {
        memset(nxt, -1, n * sizeof(nxt[0]));
        iota(tail, tail + n, 0);
        iota(par, par + n, 0);
        iota(sets, sets + n, 0);
        iota(pos, pos + n, 0);
        fill(sz, sz + n, 1);
        cnt = n;
    }
    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        int p = pos[v];
        pos[sets[p] = sets[--cnt]] = p;
        int &t = tail[u];
        nxt[t] = v;
        t = tail[v];
        return true;
    }
    string toString()
    {
        stringstream ss;
        ss << '[';
        for(int i = 0 ; i < cnt ; i++)
        {
            ss << '{';
            for(int u = sets[i] ; ~u ; u = nxt[u])
            {
                ss << u << ",}"[!~nxt[u]];
            }
            ss << ",]"[i + 1 == cnt];
        }
        return ss.str();
    }
}dsu;

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
int edj[M];
int kruskal(){
    dsu.init(n);
    int res=0;
    iota(edj,edj+ne,0);
    sort(edj,edj+ne,[](int a,int b){
       return cost[a]<cost[b];
    });
    for(int i=0;i<ne;i++){
        int e=edj[i];
        int u=to[e],v=to[e^1];
        if(dsu.merge(u,v)){
            res+=cost[e];
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
                if(i<j)
                addBiEdge(i,j,v);
            }

        printf("%d\n", kruskal());
    }
    return 0;

}

/**
 * Network of Schools POJ - 1236
 * tarjan algorithm
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 1e4 + 5, M = 1e6 + 5;
int n;

struct ADJ {
    int head[N], nxt[M], to[M], ne;


    void addEdge(int f, int t) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }

    void init(int n) {
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

} adj, Cgraph;

int vis[N], vid, stk[N], stkSz, compId[N], ncp,lw[N],dfsTime[N], curTime;

void tarjanDFS(int u){
    vis[u]=vid;
    stk[stkSz++]=u;
    lw[u]=dfsTime[u]=curTime++;
    compId[u]=-1;
    for(int e=adj.head[u]; ~e ; e=adj.nxt[e]){
        int v=adj.to[e];
        if(vis[v]!=vid){
            tarjanDFS(v); ///white
            lw[u]=min(lw[u],lw[v]);
        } else if(compId[v]==-1){ // Gray
            lw[u]=min(lw[u],lw[v]);
        }
    }

    if(lw[u]==dfsTime[u]){
        do{
            compId[stk[--stkSz]]=ncp;
        }while (stk[stkSz]!=u);

        ncp++;
    }

}

int notSrc[N], notSnk[N];

void T() {
    ++vid;
    ncp=0;
    curTime=0;
    for (int i = 0; i < n; ++i)
        if (vis[i] != vid)
            tarjanDFS(i);

    Cgraph.init(ncp);
    for (int u = 0; u < n; ++u) {
        for (int e = adj.head[u]; ~e; e = adj.nxt[e]) {
            int v = adj.to[e];
            if (compId[u] == compId[v]) continue; //intera comp edge
            Cgraph.addEdge(compId[u], compId[v]);
            notSnk[compId[u]] = vid;
            notSrc[compId[v]] = vid;
        }
    }
}

int m, q;

int main() {
    scanf("%d", &n);
    adj.init(n);
    for (int i = 0; i < n; ++i) {
        int x;
        while (scanf("%d", &x), x) {
            --x;
            adj.addEdge(i, x);
        }
    }
    T();
    int cntSrc = 0 , cntSnk = 0;
    for(int i  = 0 ; i< ncp ; ++i)
        cntSrc+=notSrc[i]!=vid , cntSnk+=notSnk[i]!=vid;
    printf("%d\n%d\n",cntSrc , ncp == 1 ? 0 : max(cntSrc,cntSnk));
    return 0;
}

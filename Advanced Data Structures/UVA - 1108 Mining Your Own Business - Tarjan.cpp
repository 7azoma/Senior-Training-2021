/**
 * Mining Your Own Business UVA - 1108
 * tarjan algorithm - undirected graph
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 5e4 + 5, M = 2 * N;

struct ADJ {
    int n, head[N], nxt[M], to[M], ne;

    void addEdge(int f, int t) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }

    void addBiEdge(int f, int t){
        addEdge(f,t);
        addEdge(t,f);
    }

    int addNode(){
        head[n]=-1;
        return n++;
    }
    void init(int n) {
        this->n=n;
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

} adj, comps;

int vis[N], vid, stk[N], stkSz,isArt[N],isBridge[M],lw[N],dfsTime[N], curTime;

void tarjanDFS(int u, int pe) {
    vis[u]=vid;
    stk[stkSz++]=u;
    lw[u]=dfsTime[u]=curTime++;
    for(int e=adj.head[u]; ~e; e=adj.nxt[e]){
        if(e==pe)continue;
        int v=adj.to[e];
        if(vis[v]!=vid){
            tarjanDFS(v,e^1);
            lw[u]=min(lw[u],lw[v]);
            if(lw[v]>=dfsTime[u]){
                if(~pe || dfsTime[v]>dfsTime[u]+1)isArt[u]=vid;
                int id=comps.addNode();
                comps.addEdge(id,u);
                do {
                    comps.addEdge(id,stk[--stkSz]);
                }while (stk[stkSz]!=v);

            }
            if(lw[v]>dfsTime[u]) {
                isBridge[e]=isBridge[e^1]=vid;
            }

        }else{
            lw[u]=min(lw[u],dfsTime[v]);

        }
    }
}

void T() {
    comps.init(0);
    ++vid;
    curTime=0;
    for (int i = 0; i < adj.n; ++i)
        if(vis[i]!=vid){
            stkSz=0;
            tarjanDFS(i,-1);
            if(!(~adj.head[i]))comps.addEdge(comps.addNode(),i);
        }


}

int m, q;

int main() {
    int cas=0;
    while(scanf("%d", &m),m){

        adj.init(0);
        while(m--){
            int u,v;
            scanf("%d%d",&u,&v);
            while(adj.n<max(u,v))adj.addNode();
            adj.addBiEdge(--u,--v);
        }


        T();

        ll numOfSolutions=1, mn=0;
        if(comps.n==1){
            mn=2;
            numOfSolutions=adj.n*(adj.n-1ll)/2;
        }else{

            for(int i=0;i<comps.n;i++){
                int cnt=0,cntArt=0;
                for (int e = comps.head[i]; ~e  ; e=comps.nxt[e]) {
                    int j=comps.to[e];
                    if(isArt[j]==vid)cntArt++;
                    else cnt++;
                }
                if(cntArt==1){
                    mn++;
                    numOfSolutions*=cnt;
                }
            }
        }
        printf("Case %d: %lld %lld\n", ++cas,mn,numOfSolutions);

    }
    return 0;
}

#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 4 * N +9;

struct ADJ {
    int head[N], nxt[M], to[M], ne,n;
    void addEdge(int f, int t) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }
    void init(int n) {
        this->n=n;
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

} adj,tmpAdj, Cgraph;

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
    for (int i = 0; i < adj.n; ++i)
        if (vis[i] != vid)
            tarjanDFS(i);

    Cgraph.init(ncp);
    for (int u = 0; u < adj.n; ++u) {
        for (int e = adj.head[u]; ~e; e = adj.nxt[e]) {
            int v = adj.to[e];
            if (compId[u] == compId[v]) continue; //intera comp edge
            Cgraph.addEdge(compId[u], compId[v]);
            notSnk[compId[u]] = vid;
            notSrc[compId[v]] = vid;
        }
    }
}
#define Var(x) ((x)<<1)
#define Not(x) ((x)^1)

void addOR(int a,int b){
    adj.addEdge(Not(a),b);
    adj.addEdge(Not(b),a);
}

void addXOR(int a,int b){
    addOR(a,b);
    addOR(Not(a),Not(b));
}

void addXNOR(int a,int b){
    addOR(Not(a),b);
    addOR(a,Not(b));
}
int m, q;
int state[N];
int main() {
    int n;
    scanf("%d%d", &n, &m);
    adj.init(2*m);
    tmpAdj.init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", state+i);
    }
    for(int i=0;i<m;i++){
        int x;
        scanf("%d",&x);
        for(int j=0;j<x;j++){
            int y;
            scanf("%d",&y);
            tmpAdj.addEdge(--y,i);
        }
    }
    for(int i=0;i<n;i++){
        vector<int>vec;
        for(int e= tmpAdj.head[i]; ~e ; e=tmpAdj.nxt[e]){
            vec.push_back(tmpAdj.to[e]);
        }
        if(state[i]){
            addXNOR(Var(vec[0]),Var(vec[1]));
        }else{
            addXOR(Var(vec[0]),Var(vec[1]));
        }

    }
    T();
    for(int i=0;i<adj.n;i+=2){
        if(compId[i]==compId[i^1]){
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}

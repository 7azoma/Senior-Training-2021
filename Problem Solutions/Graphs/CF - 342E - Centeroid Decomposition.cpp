// https://codeforces.com/problemset/problem/342/E
#include<bits/stdc++.h>

#define FAST ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
#define endl '\n'
typedef long long ll;
const int N = 2.5e5 + 10, M = 2 * N;

struct ADJ {
    int head[N], nxt[M], to[M], ne, n;
    void addEdge(int u, int v) {
        nxt[ne] = head[u];
        to[ne] = v;
        head[u] = ne++;
    }
    void addBiEdge(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }
} adj;

#define neig(u, v, e, a) for(int e=a.head[u],v;~e and (v=a.to[e],1);e=a.nxt[e])

int sz[N],nodeToIdx[N],idxToNode[2*N],depth[N],curIdx;
void dfs(int u,int p){
    sz[u]=1;
    idxToNode[nodeToIdx[u]=curIdx++]=u;
    neig(u,v,e,adj){
        if(v==p) continue;
        depth[v]=depth[u]+1;
        dfs(v,u);
        idxToNode[curIdx++]=u;
        sz[u]+=sz[v];
    }
}
int deleted[N],deletedId,cenPar[N];
void calcSz(int u,int p){
    sz[u]=1;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        calcSz(v,u);
        sz[u]+=sz[v];
    }
}
// return centeroid of tree
int decompose(int u,int p,int s){
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        if(sz[v]*2 > s) return decompose(v,u,s);
    }
    deleted[u]=deletedId;
    neig(u,v,e,adj){
        if(deleted[v]==deletedId) continue;
        calcSz(v,u);
        cenPar[decompose(v,u,sz[v])]=u;
    }
    return u;
}

int ans[N];
void centroid(int root){
    depth[root]=0;
    curIdx=0;
    deletedId++;
    dfs(root,-1);
    cenPar[ decompose(root,-1,sz[root]) ]=-1;
}
int LOG[2*N],sp[1<<18][18];
void sparceTable(){
    LOG[0]=-1;
    for (int i = 0; i < curIdx; ++i) {
        sp[i][0]=i;
        LOG[i+1]=LOG[i]+!(i&(i+1));
    }
    for (int j = 1; (1<<j) <= curIdx; ++j) {
        for (int i = 0; i+(1<<j) <= curIdx; ++i) {
            int a=sp[i][j-1];
            int b=sp[i+(1<<(j-1))][j-1];
            sp[i][j]=depth[idxToNode[a]]<depth[idxToNode[b]]?a:b;
        }
    }
}
int RMQ(int a,int b){
    int len=b-a+1;
    int lg=LOG[len];
    a=sp[a][lg],b=sp[b-(1<<lg)+1][lg];
    return depth[idxToNode[a]]<depth[idxToNode[b]]?a:b;
}

int LCA(int u,int v){
    u=nodeToIdx[u],v=nodeToIdx[v];
    if(u>v) swap(u,v);
    return idxToNode[RMQ(u,v)];
}

int dist(int u,int v){
    int l=LCA(u,v);
    return depth[u]+depth[v]-2*depth[l];
}

void makeRed(int u){
    for (int v = u; ~v  ; v=cenPar[v]) {
        ans[v]=min(ans[v],dist(u,v));
    }
}
int closestRed(int u){
    int ret=INT_MAX;
    for (int v = u; ~v  ; v=cenPar[v]){
        ret=min(ret,dist(u,v)+ans[v]);
    }
    return ret;
}
void init(){
    centroid(0);
    memset(ans,'?',adj.n*sizeof ans[0]);
    sparceTable();
    makeRed(0);
}

int main() {
    int n,m,u,v,qtp,x;
    scanf("%d%d",&n,&m);
    adj.init(n);
    for (int i = 1; i < n; ++i) {
        scanf("%d%d",&u,&v);
        --u,--v;
        adj.addBiEdge(u,v);
    }
    init();
    while (m--){
        scanf("%d%d",&qtp,&x);
        --x;
        if(qtp==1){
            makeRed(x);
        }
        else{
            printf("%d\n",closestRed(x));
        }
    }
}

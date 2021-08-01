#include <bits/stdc++.h>
#include "ext/numeric"
using namespace __gnu_cxx;
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, M = 2 * N;

int n,m;

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

int treeCentroid,sz[N],treeSz,minChild,deleted[N],delId;
void calc_SZ(int u,int p){
    sz[u]=1;
    int mx=0;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==delId) continue;
        calc_SZ(v,u);
        sz[u]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,treeSz-sz[u]);
    if(mx<minChild) {
        minChild=mx;
        treeCentroid=u;
    }
}
int val[N],arr[N],Sz;
void calc_paths(int u,int p,int curVal){
    arr[Sz++]=curVal;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==delId) continue;
        calc_paths(v,u,curVal^val[v]);
    }
}
int ones[20];
ll solve(int u,int cur,int valCenter){
    Sz=0;
    calc_paths(u,-1,cur);
    for (int i = 0; i < Sz; ++i) {
        for (int j = 0; j < 20; ++j) {
            ones[j]+=((arr[i]>>j)&1);
        }
    }
    ll ret=0;
    for (int i = 0; i < Sz; ++i) {
        for (int j = 0; j < 20; ++j) {
            bool x=((arr[i]>>j)&1);
            bool y=((valCenter>>j)&1);
            ones[j]-=x;
            ret+=((x^y)?(Sz-i-1-ones[j]):ones[j])*(1ll<<j);
        }
    }
    return ret;
}
ll decompose(int u){
    ll ret=solve(u,0,val[u]);
    deleted[u]=delId;
    neig(u,v,e,adj) {
        if (deleted[v] == delId) continue;
        ret -= solve(v,val[v],val[u]);
        treeSz = minChild = sz[v];
        calc_SZ(v,-1);
        calc_SZ(treeCentroid,-1);
//        cpar[treeCentroid]=u;
//        centroidAdj.addEdge(u,treeCentroid);
        ret+=decompose(treeCentroid);
    }
    return ret;
}
ll centroid(){
    treeSz=minChild=adj.n;
    delId++;
    calc_SZ(0,-1);
    calc_SZ(treeCentroid,-1);
//    cpar[treeCentroid]=-1;
    return decompose(treeCentroid);
}

int main(){

    scanf("%d",&n);
    ll ret=0;
    adj.init(n);
    for (int i = 0; i < n; ++i)
        scanf("%d",val+i),ret+=val[i];
    int u,v;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d",&u,&v);
        adj.addBiEdge(--u,--v);
    }
    printf("%lld",centroid()+ret);
}



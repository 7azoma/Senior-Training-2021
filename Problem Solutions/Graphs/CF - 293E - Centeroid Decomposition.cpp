#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, M = 2 * N;
int L,W;
ll res;

struct ADJ {
    int head[N], nxt[M],cost[M], to[M], ne, n;
    void addEdge(int u, int v,int c) {
        nxt[ne] = head[u];
        to[ne] = v;
        cost[ne]=c;
        head[u] = ne++;
    }
    void addBiEdge(int u, int v,int c) {
        addEdge(u, v,c);
        addEdge(v, u,c);
    }
    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }
} adj;
#define neig(u, v, e, a) for(int e=a.head[u],v;~e and (v=a.to[e],1);e=a.nxt[e])
//centroid
int numberOfnodes,treeCentroid,mincompSz,sz[N],deleted[N],delId,cenPar[N];
void dfs(int u,int p){
    sz[u]=1;
    int mx=0;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==delId) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,numberOfnodes-sz[u]);
    if(mx<mincompSz) treeCentroid=u,mincompSz=mx;
}


pair<int,int> arr[N];
int arrSz;
void dfs(int u,int p,int l,int w){
    arr[arrSz++]={w,l};
    neig(u,v,e,adj){
        if(p==v or deleted[v]==delId) continue;
        dfs(v,u,l+1,w+adj.cost[e]);
    }
}
struct BIT
{
    int tree[N];
    void init()
    {
        memset(tree, 0, sizeof tree);
    }
    void add(int pos, int val)
    {
        for(++pos ; pos <= N ; pos += (pos & (-pos))) tree[pos - 1] += val;
    }
    int get(int pos)
    {
        if(pos<0) return 0;
        int ret = 0;
        for(++pos ; pos ; pos -= (pos & (-pos))) ret += tree[pos - 1];
        return ret;
    }
}bit;
ll solve(int u,int l,int w){//l:from current centeroid,w:weight from current centroid
    arrSz=0;
    dfs(u,-1,l,w);
    sort(arr,arr+arrSz);
    ll res=0;
    int st=0,en=arrSz-1;
    for (int i = 0; i < arrSz; ++i) {
        bit.add(arr[i].second,1);
    }
    while (st<en){
        if(arr[st].first+arr[en].first<=W){
            bit.add(arr[st].second,-1);
            res+=bit.get(L-arr[st++].second);
        }
        else{
            bit.add(arr[en--].second,-1);
        }
    }
    bit.add(arr[st].second,-1);
    return res;
}
int decompose(int u){
    deleted[u]=delId;
    res+=solve(u,0,0);
    neig(u,v,e,adj){
        if(deleted[v]==delId) continue;
        res-=solve(v,1,adj.cost[e]);
        numberOfnodes=mincompSz=sz[v];
        dfs(v,u);
        dfs(treeCentroid,-1);
        cenPar[treeCentroid]=u;
        decompose(treeCentroid);
    }
}
void centroid(int root){
    delId++;
    dfs(root,-1);
    dfs(treeCentroid,-1);
    cenPar[ treeCentroid ]=-1;
    res=0;
    decompose(treeCentroid);
}
int main() {
    int n,v,w;
    scanf("%d%d%d",&n,&L,&W);
    adj.init(n);
    for (int i = 1; i < n; ++i) {
        scanf("%d%d",&v,&w);
        v--;
        adj.addBiEdge(i,v,w);
    }
    centroid(0);
    printf("%I64d\n",res);
}

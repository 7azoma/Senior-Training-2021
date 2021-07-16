// https://www.codechef.com/problems/QRYLAND
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
int val[N], par[N], sz[N], heavyCH[N], depth[N];

void dfs(int u) {
    sz[u] = 1;
    heavyCH[u] = -1;
    neig(u, v, e, adj) {
        if (v == par[u]) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
        sz[u] += sz[v];
        if (!~heavyCH[u] or sz[heavyCH[u]] < sz[v]) {
            heavyCH[u] = v;
        }
    }
}

int idxToNode[N], nodeToIdx[N], curIdx, chainHead[N];

void HLD(int u, int ch) {
    idxToNode[nodeToIdx[u] = curIdx++] = u;
    chainHead[u] = ch;
    if (~heavyCH[u]) {
        HLD(heavyCH[u], ch);
    }
    neig(u, v, e, adj) {
        if (v == par[u] or v == heavyCH[u]) continue;
        HLD(v, v);
    }
}
valarray<ll> p(2);

valarray<ll> power[(int)2.5e5+1];

valarray<ll> prefix[(int)2.5e5+1];

valarray<ll> mod={(ll)1e9+9,(ll)1e9+7};
struct node {
    valarray<ll> sum;

    void set(int Val) {
        sum=power[Val];
    }
};


bool isPrime(ll x){
    for (int i = 2; i <= x/i; ++i) {
        if(!(x%i)) return 0;
    }
    return 1;
}

ll nextPrime(ll x){
    while (!isPrime(x)) x++;
    return x;
}

node tree[1 << 19];

node merge(const node &lf, const node &rt) {
    node ret;
    ret.sum = (lf.sum + rt.sum)%mod;
    return ret;
}

void build(int ni = 0, int ns = 0, int ne = curIdx) {
    if (ns == ne) {
        int pos = idxToNode[ns];
        tree[ni].set(val[pos]);
        return;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    build(lf, ns, mid);
    build(rt, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[rt]);
}

node query(int qs, int qe, int ni = 0, int ns = 0, int ne = curIdx) {
    if (ns > qe or ne < qs) {
        return {{0ll, 0ll}};
    }
    if (ns >= qs and ne <= qe) return tree[ni];
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return merge(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
}

void update(int idx, int Val, int ni = 0, int ns = 0, int ne = curIdx) {
    if (ns > idx or ne < idx) {
        return;
    }
    if (ns == ne) return tree[ni].set(Val), void();
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(idx, Val, lf, ns, mid), update(idx, Val, rt, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[rt]);
}


bool getContiguos(int u, int v) {
    int SZ=0;
    node un = {{0ll,0ll}};
    node vn = {{0ll,0ll}};

    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]])
            swap(u, v), swap(un, vn);

        node tmp = query(nodeToIdx[chainHead[u]], nodeToIdx[u]);
        SZ+=nodeToIdx[u]-nodeToIdx[chainHead[u]]+1;
        un = merge(tmp, un);
        u = par[chainHead[u]];
    }
    if (depth[v] < depth[u]) swap(u, v), swap(un, vn);
    node tmp = query(nodeToIdx[u], nodeToIdx[v]);
    vn = merge(tmp, vn);
    SZ+=nodeToIdx[v]-nodeToIdx[u]+1;
    tmp=merge(un,vn);
    return (tmp.sum==prefix[SZ-1]).min();
}
void Hash(){
    p[0]=nextPrime(2.5e5);
    p[1]=nextPrime(p[0]+1);
    power[0]={1,1};
    prefix[0]={1,1};
    for (int i = 1; i <= (int)2.5e5; ++i) {
        power[i]=(power[i-1]*p)%mod;
        prefix[i]=(prefix[i-1]+power[i])%mod;
    }
}

int main() {

    Hash();
    int t,n,q,u,v;
    scanf("%d",&t);
    while (t--){
        curIdx=0;
        scanf("%d%d",&n,&q);
        adj.init(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d",val+i);
            val[i]--;
        }
        for (int i = 1; i < n; ++i) {
            scanf("%d%d",&u,&v);
            adj.addBiEdge(--u,--v);
        }
        dfs(0);
        HLD(0,0);
        build();
        int qtp,x,y;
        while (q--){
            scanf("%d%d%d",&qtp,&x,&y);
            --x,--y;
            if(qtp==1){
                puts((getContiguos(x,y)?"Yes":"No"));
            }
            else{//updatepoint
                update(nodeToIdx[x],y);
            }
        }
    }

}

// https://www.spoj.com/problems/GSS7/
#include<bits/stdc++.h>

#define FAST ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
#define endl '\n'
const int N = 1e5 + 10, M = 2 * N;

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

struct node {
    int sum, pre, suf, mx, lazy;

    void set(int Val) {
        lazy = INT_MIN;
        sum = Val;
        pre = suf = mx = max(Val, 0);
    }

    void setLazy(int Val, int ns, int ne) {
        set(Val * (ne - ns + 1));
        lazy = Val;
    }

    void Swap() {
        swap(pre, suf);
    }
};

node tree[1 << 18];

void pushDown(int ni, int ns, int ne) {
    if (ns == ne or tree[ni].lazy == INT_MIN) return;
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    tree[lf].setLazy(tree[ni].lazy, ns, mid);
    tree[rt].setLazy(tree[ni].lazy, mid + 1, ne);
    tree[ni].lazy = INT_MIN;
}

node merge(const node &lf, const node &rt) {
    node ret;
    ret.lazy = INT_MIN;
    ret.sum = lf.sum + rt.sum;
    ret.pre = max(lf.pre, lf.sum + rt.pre);
    ret.suf = max(rt.suf, rt.sum + lf.suf);
    ret.mx = max({rt.mx, lf.mx, lf.suf + rt.pre});
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
        return {0, -(int) 1e9, -(int) 1e9, -(int) 1e9, INT_MIN};
    }
    if (ns >= qs and ne <= qe) return tree[ni];
    pushDown(ni, ns, ne);
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return merge(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
}

void update(int qs, int qe, int Val, int ni = 0, int ns = 0, int ne = curIdx) {
    if (ns > qe or ne < qs) {
        return;
    }
    if (ns >= qs and ne <= qe) return tree[ni].setLazy(Val, ns, ne), void();
    pushDown(ni, ns, ne);
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(qs, qe, Val, lf, ns, mid), update(qs, qe, Val, rt, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[rt]);
}

void setVal(int u, int v, int Val) {
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]])
            swap(u, v);
        update(nodeToIdx[chainHead[u]], nodeToIdx[u], Val);
        u = par[chainHead[u]];
    }
    if (depth[v] < depth[u]) swap(u, v);
    update(nodeToIdx[u], nodeToIdx[v], Val);
}

int getMax(int u, int v) {
    node un = {0, -(int) 1e9, -(int) 1e9, -(int) 1e9, INT_MIN};
    node vn = {0, -(int) 1e9, -(int) 1e9, -(int) 1e9, INT_MIN};

    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]])
            swap(u, v), swap(un, vn);

        node tmp = query(nodeToIdx[chainHead[u]], nodeToIdx[u]);
        un = merge(tmp, un);
        u = par[chainHead[u]];
    }
    if (depth[v] < depth[u]) swap(u, v), swap(un, vn);
    node tmp = query(nodeToIdx[u], nodeToIdx[v]);
    vn = merge(tmp, vn);
    vn.Swap();
    return merge(vn, un).mx;
}

int main() {
    int n,u,v;
    scanf("%d",&n);
    adj.init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d",val+i);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d%d",&u,&v);
        adj.addBiEdge(--u,--v);
    }
    dfs(0);
    HLD(0,0);
    build();

    int q,qtyp,a,b,c;
    scanf("%d",&q);
    while (q--){
        scanf("%d%d%d",&qtyp,&a,&b);
        if(qtyp==1){
            printf("%d\n",getMax(--a,--b));
        }
        else{
            scanf("%d",&c);
            setVal(--a,--b,c);
        }
    }
}

// http://www.usaco.org/index.php?page=viewproblem2&cpid=842
// https://vjudge.net/problem/LibreOJ-2871
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, M = 2 * N;


struct ADJ {
    int nxt[M], head[N], to[M], ne, n;

    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }

    void addEdge(int u, int v) {
        to[ne] = v;
        nxt[ne] = head[u];

        head[u] = ne++;
    }

    void addBiEdge(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
} adj;

#define nieg(a, u, v, e) for(int e = a.head[u],v;~e && (v=a.to[e],1);e=a.nxt[e])
int n, m, SZ[N], par[N], hevChild[N], nodetoIdx[N], idxToNode[N], chain[N], depth[N], curTime, parEdg[N];

void dfs(int u) {
    SZ[u] = 1;
    hevChild[u] = -1;
    nieg(adj, u, v, e) {
        if (v == par[u]) continue;
        par[v] = u;
        parEdg[v] = e / 2;
        depth[v] = 1 + depth[u];
        dfs(v);
        if (hevChild[u] == -1 || SZ[hevChild[u]] < SZ[v])
            hevChild[u] = v;
        SZ[u] += SZ[v];

    }
}

void HLD(int u, int cId) {
    idxToNode[nodetoIdx[u] = curTime++] = u;
    chain[u] = cId;
    if (~hevChild[u])
        HLD(hevChild[u], cId);
    nieg(adj, u, v, e) {
        if (par[u] == v || hevChild[u] == v) continue;
        HLD(v, v);
    }
}

const int OO = INT_MAX;


struct node {
    int lazy, val;

    node() : lazy(INT_MAX), val(INT_MAX) {}

    void setLazy(int x) {
        val = min(val, x);
        lazy = min(lazy, x);
    }

} tree[1 << 17];

void pushDown(int ni, int ns, int ne) {
    node &nd = tree[ni];
    if (ns == ne || nd.lazy == INT_MAX) return;
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    tree[lf].setLazy(nd.lazy);
    tree[rt].setLazy(nd.lazy);
    nd.lazy = INT_MAX;
}

void pushUp(int ni) {
    int lf = 2 * ni + 1, rt = lf + 1;
    tree[ni].val = min(tree[lf].val, tree[rt].val);
}

void updateRange(int qs, int qe, int qv, int ni = 0, int ns = 0, int ne = curTime - 1) {
    node &nd = tree[ni];
    if (qs > ne || ns > qe) return;
    if (ns >= qs && ne <= qe) {
        nd.setLazy(qv);
        return;
    }
    pushDown(ni, ns, ne);
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    updateRange(qs, qe, qv, lf, ns, mid);
    updateRange(qs, qe, qv, rt, mid + 1, ne);
    pushUp(ni);
}

void update(int u, int v, int c) {
    while (chain[u] != chain[v]) {
        if (depth[chain[u]] < depth[chain[v]])
            swap(u, v);
        updateRange(nodetoIdx[chain[u]], nodetoIdx[u], c);
        u = par[chain[u]];
    }
    if (depth[u] < depth[v])
        swap(u, v);
    if (u != v)
        updateRange(nodetoIdx[v] + 1, nodetoIdx[u], c);
}

int query(int idx, int ni = 0, int ns = 0, int ne = curTime - 1) {
    if (idx > ne || idx < ns) return OO;
    if (ns == ne)
        return tree[ni].val;
    pushDown(ni, ns, ne);
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return min(query(idx, lf, ns, mid), query(idx, rt, mid + 1, ne));
}

int answer[N];

int main() {

    scanf("%d%d", &n, &m);
    int u, v, c;
    adj.init(n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0);
    HLD(0, 0);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        update(u, v, c);
    }
    for (int i = 1; i < n; ++i)
        answer[parEdg[i]] = query(nodetoIdx[i]);

    for (int i = 0; i < n - 1; ++i)
        printf("%d\n", answer[i]==OO ? -1 : answer[i]);
    return 0;
}

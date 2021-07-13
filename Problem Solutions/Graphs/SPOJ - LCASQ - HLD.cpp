// https://vjudge.net/problem/SPOJ-LCASQ
//SPOJ-LCASQ
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
int n, m, SZ[N], par[N], hevChild[N], nodetoIdx[N], idxToNode[N], chain[N], depth[N], curTime;

void dfs(int u) {
    SZ[u] = 1;
    hevChild[u] = -1;
    nieg(adj, u, v, e) {
        if (v == par[u]) continue;
        par[v] = u;
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

int LCA(int u, int v) {
    while (chain[u] != chain[v]) {
        if (depth[chain[u]] < depth[chain[v]])
            swap(u, v);
        u = par[chain[u]];
    }
    return depth[u] < depth[v] ? u : v;
}

int main() {

    scanf("%d", &n);
    int u, v, c;
    adj.init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &v);
            adj.addBiEdge(i, v);
        }
    }
    int q;
    dfs(0);
    HLD(0, 0);
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &u, &v);
        printf("%d\n", LCA(u, v));
    }

    return 0;
}

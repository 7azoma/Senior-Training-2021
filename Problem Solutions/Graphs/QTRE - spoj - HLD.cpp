// https://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, M = 2 * N;


struct ADJ {
    int nxt[M], head[N], to[M], ne, n, cst[N];

    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }

    void addEdge(int u, int v, int c) {
        to[ne] = v;
        nxt[ne] = head[u];
        cst[ne] = c;
        head[u] = ne++;
    }

    void addBiEdge(int u, int v, int c) {
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
} adj;

#define nieg(a, u, v, e) for(int e = a.head[u],v;~e && (v=a.to[e],1);e=a.nxt[e])
int n, m, SZ[N], par[N], hevChild[N], nodetoIdx[N], idxToNode[N], chain[N], depth[N], curTime, val[N], toNode[N];

void dfs(int u) {
    SZ[u] = 1;
    hevChild[u] = -1;
    nieg(adj, u, v, e) {
        if (v == par[u]) continue;
        par[v] = u;
        val[v] = adj.cst[e];
        toNode[e / 2] = v;
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


struct node {
    int val;
} tree[1 << 17];

void pushUp(int ni) {
    int lf = 2 * ni + 1, rt = lf + 1;
    tree[ni].val = max(tree[lf].val, tree[rt].val);
}

void build(int ni = 0, int ns = 0, int ne = curTime - 1) {
    if (ns == ne) {
        tree[ni].val = val[idxToNode[ns]];
        return;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    build(lf, ns, mid);
    build(rt, mid + 1, ne);
    pushUp(ni);

}

void updateValue(int idx, int v, int ni = 0, int ns = 0, int ne = curTime - 1) {
    node &nd = tree[ni];
    if (idx > ne || ns > idx) return;
    if (ns == ne) {
        tree[ni].val = v;
        return;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    updateValue(idx, v, lf, ns, mid);
    updateValue(idx, v, rt, mid + 1, ne);
    pushUp(ni);
}

int queryRange(int qs, int qe, int ni = 0, int ns = 0, int ne = curTime - 1) {
    if (qs > ne || qe < ns) return INT_MIN;
    if (ns >= qs && ne <= qe) {
        return tree[ni].val;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return max(queryRange(qs, qe, lf, ns, mid), queryRange(qs, qe, rt, mid + 1, ne));
}

int getAns(int u, int v) {
    int ans = INT_MIN;
    while (chain[u] != chain[v]) {
        if (depth[chain[u]] < depth[chain[v]])
            swap(u, v);
        ans = max(ans, queryRange(nodetoIdx[chain[u]], nodetoIdx[u]));
        u = par[chain[u]];
    }
    if (depth[u] < depth[v])
        swap(u, v);
    if (u != v)
        ans = max(ans, queryRange(nodetoIdx[v] + 1, nodetoIdx[u]));
    return ans;
}

char str[50];
int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        curTime = 0;
        scanf("%d", &n);
        int u, v, c;
        adj.init(n);
        for (int i = 0; i < n - 1; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            --u, --v;
            adj.addBiEdge(u, v, c);
        }
        dfs(0);
        HLD(0, 0);
        build();
        while (1) {
            scanf("%s", str);
            if (str[0] == 'D') break;
            scanf("%d%d", &u, &v);
            if (str[0] == 'C')
                updateValue(nodetoIdx[toNode[--u]], v);
            else
                printf("%d\n", u != v ? getAns(--u, --v) : 0);

        }
    }
    return 0;
}

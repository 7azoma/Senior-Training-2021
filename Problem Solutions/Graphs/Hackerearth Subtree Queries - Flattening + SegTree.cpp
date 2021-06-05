#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 1e4 + 5, M = 1e6 + 5;
int head[N], nxt[M], to[M], ne, n, m, q;

void addEdge(int f, int t) {
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
}

void addBiEdge(int u, int v) {
    addEdge(u, v);
    addEdge(v, u);
}

void init() {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}

int u, v;
int st[N], et[N], ord[N], tim;


void dfs(int u, int par) {
    ord[tim] = u;
    st[u] = tim++;
    for (int e = head[u]; ~e; e = nxt[e]) {
        int v = to[e];
        if (v == par) continue;
        dfs(v, u);
    }
    et[u] = tim - 1;
}

int val[N], tree[1 << 18];

void build(int ni = 0, int ns = 0, int ne = tim - 1) {
    if (ns == ne) {
        int u = ord[ns];
        tree[ni] = val[u];
        return;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    build(lf, ns, mid);
    build(rt, mid + 1, ne);
    tree[ni] = __gcd(tree[lf], tree[rt]);
}

void update(int p, int v, int ni = 0, int ns = 0, int ne = tim - 1) {
    if (p < ns || p > ne) return;
    if (ns == ne) {
        tree[ni] = v;
        return;
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(p, v, lf, ns, mid);
    update(p, v, rt, mid + 1, ne);
    tree[ni] = __gcd(tree[lf], tree[rt]);
}

int query(int qs, int qe, int ni = 0, int ns = 0, int ne = tim - 1) {
    if (qs > ne || ns > qe) return 0;
    if (ns >= qs && ne <= qe) {
        return tree[ni];
    }
    int lf = 2 * ni + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return __gcd(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i)
        scanf("%d", val + i);
    init();
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        --u, --v;
        addBiEdge(u, v);
    }
    dfs(0, -1);
    build();
    while (q--) {
        int typ, x, v;
        scanf("%d%d", &typ, &x);
        if (typ == 1) {
            scanf("%d", &v);
            update(st[x - 1], v);
        } else
            printf("%d\n", query(st[x - 1],et[x-1]));
    }
    return 0;
}

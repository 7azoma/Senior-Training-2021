//vjugde ->LibreOJ-2871
//usaco Disruption
// http://www.usaco.org/index.php?page=viewproblem2&cpid=842
// https://vjudge.net/problem/LibreOJ-2871
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, M = 2 * N;
int n, m;

struct adj {
    int nxt[M], head[N], to[M], ne, n, cst[M];

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
} org, ext;

int stTime[N], finishTime[N], ord[N], SZ[N], curTime, answer[N], par[N];
#define nieg(a, u, v, e) for(int e = a.head[u],v;~e && (v=a.to[e],1);e=a.nxt[e])

//compute size of each subtree
void dfs(int u) {
    SZ[u] = 1;
    ord[stTime[u] = curTime++] = u;
    nieg(org, u, v, e) {
        if ((e ^ 1) == par[u]) continue;
        par[v] = e;
        dfs(v);
        SZ[u] += SZ[v];
    }
    finishTime[u] = curTime - 1;
}

void add(int eId, set<pair<int, int>> &activeEdges) {
    //emplace/insert returns a pair < the inserted val , bool hasInserted? >
    auto p = activeEdges.emplace(ext.cst[eId], eId / 2);
    if (!p.second)
        activeEdges.erase(p.first);
}

//insert nigbhours
void insertEdges(int u, set<pair<int, int>> &activeEdges) {
    nieg(ext, u, v, e) {
        add(e, activeEdges);
    }
}

set<pair<int, int>> smallToLarge(int u) {
    set<pair<int, int>> activeEdges;
    nieg(org, u, v, e) {
        if ((e ^ 1) == par[u]) continue;
        if (SZ[v] * 2 >= SZ[u]) {
            activeEdges = smallToLarge(v);
            continue;
        }
        smallToLarge(v);
    }
    
    insertEdges(u, activeEdges);
    nieg(org, u, v, e) {
        if ((e ^ 1) == par[u]) continue;

        if (SZ[v] * 2 >= SZ[u]) continue;

        for (int x = stTime[v]; x <= finishTime[v]; ++x)
            insertEdges(ord[x], activeEdges);

    }
    if (u) {
        if (activeEdges.empty())
            answer[par[u] / 2] = -1;
        else
            answer[par[u] / 2] = activeEdges.begin()->first;
    }
    return activeEdges;
}

int main() {

    scanf("%d%d", &n, &m);
    int u, v, c;
    org.init(n);
    ext.init(n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        --u, --v;
        org.addBiEdge(u, v, 0);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        ext.addBiEdge(u, v, c);
    }
    dfs(0);
    smallToLarge(0);
    for (int i = 0; i < n-1; ++i)
        printf("%d\n", answer[i]);
    return 0;
}

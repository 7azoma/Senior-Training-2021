#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10, M = 2*N + 10;

int head[N], nxt[M], to[M], ne, n;

void addEdge(int f, int t) {
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
}

void addBiEdge(int f, int t) {
    addEdge(f, t);
    addEdge(t, f);
}

void init(int n) {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}

struct Data {
    unordered_map<int, int> freq;
    int mx;
    ll sum;

    Data() : mx(0), sum(0) {

    }

    void add(int col) {
        int f = ++freq[col];
        if (f > mx)
            mx = f, sum = 0;
        if (f == mx)
            sum += col;
    }
};

int c[N];
int st[N], fi[N], dfsOrder[N], sz[N];
int pa[N];
ll ans[N];
int curTime;

void dfs(int u) {
    dfsOrder[st[u] = curTime++] = u;
    sz[u] = 1;
    for (int e = head[u]; ~e; e = nxt[e]) {
        int v = to[e];
        if(pa[u] == v)
            continue;
        pa[v] = u;
        dfs(v);
        sz[u] += sz[v];
    }
    fi[u] = curTime - 1;
}

void extend(Data &temp, int i){
    for (int j = st[i]; j <= fi[i]; ++j) {
        int u = dfsOrder[j];
        temp.add(c[u]);
    }
}

Data smallToLarge(int u){
    Data te;
    int big = -1;
    for (int e = head[u]; ~e; e=nxt[e]) {
        int v = to[e];
        if(pa[u] == v)
            continue;
        if(sz[v]*2 > sz[u])
            big = v;
        else
            smallToLarge(v);
    }
    if(big != -1){
        te = smallToLarge(big);
    }
    te.add(c[u]);
    for (int e = head[u]; ~e; e=nxt[e]){
        int v = to[e];
        if(pa[u] == v || v == big)
            continue;
        extend(te, v);
    }
    ans[u] = te.sum;
    return te;
}



int main() {
    scanf("%d", &n);
    init(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", c + i);
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v;
        addBiEdge(u, v);
    }
    dfs(0);
    smallToLarge(0);
    for (int i = 0; i < n; ++i) {
        printf("%lld ", ans[i]);
    }
}

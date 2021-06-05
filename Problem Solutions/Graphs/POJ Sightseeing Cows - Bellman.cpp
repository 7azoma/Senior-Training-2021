#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int N = 1e3 + 10, M = 1e4 + 10;
const double eps = 1e-8;

int head[N], nxt[M], to[M], ne, n, vid, inque[N];
double cost[M], cost2[M], dis[M];
int fun[N];

void reWeight(double avg) {
    for (int i = 0; i < ne; ++i) {
        cost[i] = avg * cost2[i] - fun[to[i]];
    }
}


void addEdge(int f, int t, int cst) {
    nxt[ne] = head[f];
    to[ne] = t;
    cost[ne] = cost2[ne] = cst;
    head[f] = ne++;
}

void addBiEdge(int f, int t, int cst) {
    addEdge(f, t, cst);
    addEdge(t, f, cst);
}

void init(int n) {
    memset(head, -1, n * sizeof head[0]);
    ne = 0;
}

bool bellman(int src) {
    queue<int> q;
    fill(dis, dis+n, 1e18);
    dis[src] = 0;
    inque[src] = ++vid;
    int cnt = n;
    q.push(src);
    while (cnt-- && q.size()) {
        int s = q.size();
        while (s--) {
            int u = q.front();
            q.pop();
            inque[u] = 0;
            for (int e = head[u]; ~e; e = nxt[e]) {
                int v = to[e];
                double d = dis[u] + cost[e];
                if (dis[v] > d) {
                    if (!cnt) {
                        return false;
                    }
                    dis[v] = d;
                    if (inque[v] != vid) {
                        inque[v] = vid;
                        q.push(v);

                    }

                }
            }
        }
    }
    return true;
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    int mxFun = -1;
    init(n + 1);
    for (int i = 0; i < n; ++i) {
        scanf("%d", fun + i);
        mxFun = max(mxFun, fun[i]);
        addEdge(n, i, 0);
    }

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        --u;
        --v;
        addEdge(u, v, c);
    }
    double st = 0;
    for (double sz = mxFun / 2.; sz > eps; sz *= 0.5) {
        reWeight(st + sz);
        if (!bellman(n))
            st += sz;
    }
    cout << fixed << setprecision(2);
    cout << st << "\n";
}

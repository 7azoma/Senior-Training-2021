/*
TASK: castle
LANG: C++14
 */

#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 51 * 50;

struct DSU
{
    int par[N], sz[N], sets[N], pos[N], tail[N], nxt[N], cnt;
    void init(int n)
    {
        memset(nxt, -1, n * sizeof(nxt[0]));
        iota(tail, tail + n, 0);
        iota(par, par + n, 0);
        iota(sets, sets + n, 0);
        iota(pos, pos + n, 0);
        fill(sz, sz + n, 1);
        cnt = n;
    }
    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        int p = pos[v];
        pos[sets[p] = sets[--cnt]] = p;
        int &t = tail[u];
        nxt[t] = v;
        t = tail[v];
        return true;
    }
    string toString()
    {
        stringstream ss;
        ss << '[';
        for(int i = 0 ; i < cnt ; i++)
        {
            ss << '{';
            for(int u = sets[i] ; ~u ; u = nxt[u])
            {
                ss << u << ",}"[!~nxt[u]];
            }
            ss << ",]"[i + 1 == cnt];
        }
        return ss.str();
    }
}dsu;

int main()
{
    freopen("castle.in", "rt", stdin);
    freopen("castle.out", "wt", stdout);
    int n, m, x;
    scanf("%d%d", &m, &n);
    dsu.init(n * m);
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < m ; j++)
        {
            scanf("%d", &x);
            int di = 0, dj = -1;
            for(int k = 0 ; k < 4 ; k++)
            {
                if(!((x >> k) & 1))
                {
                    int ni = i + di;
                    int nj = j + dj;
                    dsu.merge(i * m + j, ni * m + nj);
                }
                swap(di, dj);
                if(k == 1) dj *= -1;
            }
        }
    }
    printf("%d\n", dsu.cnt);
    int mx = 0, ii, jj;
    char cc;
    for(int i = 0 ; i < dsu.cnt ; i++)
    {
        mx = max(mx, dsu.sz[dsu.sets[i]]);
    }
    printf("%d\n", mx);
    mx = 0;
    for(int j = 0 ; j < m ; j++)
    {
        for(int i = n - 1 ; i >= 0 ; i--)
        {
            int di = -1, dj = 0;
            char c = 'N';
            for(int k = 0 ; k < 2 ; k++)
            {
                int ni = i + di;
                int nj = j + dj;
                int n1, n2;
                if(ni >= 0 and ni < n and nj >= 0 and nj < m and (n1 = dsu.find(i * m + j)) != (n2 = dsu.find((ni * m + nj))))
                {
                    if(dsu.sz[n1] + dsu.sz[n2] > mx)
                    {
                        ii = i, jj = j, cc = c;
                        mx = dsu.sz[n1] + dsu.sz[n2];
                    }
                }
                di = 0, dj = 1;
                c = 'E';
            }
        }
    }
    printf("%d\n%d %d %c\n", mx, ii + 1, jj + 1, cc);
    return 0;
}

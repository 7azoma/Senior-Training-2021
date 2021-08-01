#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;

const int N = 31;

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

map<vector<int>, double> dp;

double solve(vector<int> v) {
    if(v.size()==1) return 0; //one component
    double &ret = dp.emplace(v, -1).first->second;
    if (ret != -1) return ret;
    double p = 0, q = 0;
    for (int i = 0; i < v.size(); ++i) {
        p += v[i] * (v[i] - 1) / 2;
        for (int j = i + 1; j < v.size(); ++j) {
            vector<int> vv = v;
            vv[i] += vv[j];
            swap(vv[j], vv.back());
            vv.pop_back();
            sort(vv.begin(), vv.end());
            q += (v[i] * v[j] / (n * (n - 1.0) / 2)) * (1 + solve(vv));
        }
    }
    p/=(n*(n-1)/2);
    return ret=(p+q)/(1-p);
}


int main() {
    int m,u,v;
    while (~scanf("%d%d",&n,&m)) {

        dsu.init(n);
        while (m--){
            scanf("%d%d", &u, &v);
            dsu.merge(--u, --v);
        }
        vector<int> v;
        for(int i = 0 ; i < dsu.cnt ; i++){
            v.push_back(dsu.sz[dsu.sets[i]]);
        }
        sort(v.begin(),v.end());
        printf("%.6lf\n",solve(v));
    }
}

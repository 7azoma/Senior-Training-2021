#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
struct DSU
{
    int par[N], szx[N], szy[N];
    long long ans;
    struct op {
        int v, parV, u, szxU, szyU;
        long long ans;
    };
    stack<op> sk;
    void init(int n)
    {
        iota(par, par + 2 * n, 0);
        fill(szx, szx + n, 1);
        fill(szy + n, szy + 2 * n, 1);
        ans = 0;
    }
    int find(int x)
    {
        if(par[x] == x) return x;
        op operation={x,par[x],-1,-1,-1, -1};
        sk.push(operation);
        return par[x] = find(par[x]);
    }
    bool merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(szx[u]+szy[u] < szx[v]+szy[v]) swap(u, v);
        op operation={v,par[v],u,szx[u], szy[u],ans};
        sk.push(operation);
        ans -= szx[u] * 1ll * szy[u];
        ans -= szx[v] * 1ll * szy[v];
        par[v] = u;
        szx[u] += szx[v];
        szy[u] += szy[v];
        ans += szx[u] * 1ll * szy[u];
        return true;
    }
    void rollBack(int stkSz){
        while (sk.size()>stkSz){
            op operation=sk.top(); sk.pop();
            par[operation.v]=operation.parV;
            if(operation.u==-1) continue;
            szx[operation.u]=operation.szxU;
            szy[operation.u]=operation.szyU;
            ans = operation.ans;
        }
    }
}dsu;
int q;
long long ans[N];

struct node{
    vector<pair<int,int>> v;
} seg[1<<20];
void addEdge(int qs,int qe,pair<int,int> e,int ni=0,int ns=0,int ne=q){
    if(qe<ns or qs>ne) return;
    if(ns>=qs and ne<=qe){
        seg[ni].v.push_back(e);
        return;
    }
    int lf=2*ni+1,rt=lf+1,mid=ns+(ne-ns)/2;
    addEdge(qs,qe,e,lf,ns,mid);
    addEdge(qs,qe,e,rt,mid+1,ne);
}

void dfs(int ni=0,int ns=0,int ne=q){
    int sz=dsu.sk.size();
    for (auto it:seg[ni].v){
        dsu.merge(it.first,it.second);
    }
    if(ns!=ne){
        int lf=2*ni+1,rt=lf+1,mid=ns+(ne-ns)/2;
        dfs(lf,ns,mid);
        dfs(rt,mid+1,ne);
    }
    else {
        ans[ns] = dsu.ans;
    }
    dsu.rollBack(sz);
}

int main(){
    //freopen("input.txt", "rt", stdin);
    //freopen("input.txt", "rt", stdout);
    dsu.init((int)3e5);
    int u, v;
    scanf("%d", &q);
    map<pair<int, int>, int> mp;
    for (int i =0; i < q; ++i) {
        scanf("%d%d", &u, &v);
        --u; --v;
        v += (int)3e5;
        auto xx = mp.insert({{u, v}, i});
        if (!xx.second) {
            addEdge(xx.first-> second, i-1, {u, v});
            mp.erase(xx.first);
        }
    }
    for (auto i : mp) {
        addEdge(i.second, q, i.first);
    }
    dfs();
    for (int i = 0; i < q; ++i) {
        printf("%lld ", ans[i]);
    }

return 0;
}


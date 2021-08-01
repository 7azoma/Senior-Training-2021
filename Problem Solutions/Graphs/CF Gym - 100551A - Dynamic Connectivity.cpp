#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+1;

struct DSU
{
    int par[N], sz[N],cnt;
    struct op{
        int v,parV,u,szU,cnt;
    };
    stack<op> sk;
    void init(int n)
    {
        iota(par, par + n, 0);
        fill(sz, sz + n, 1);
        cnt = n;
    }
    int find(int x)
    {
        if(par[x] == x) return x;
        op operation={x,par[x],-1,-1,-1};
        sk.push(operation);
        return par[x] = find(par[x]);
    }
    bool merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        op operation={v,par[v],u,sz[u],cnt};
        sk.push(operation);
        par[v] = u;
        cnt--;
        sz[u] += sz[v];
        return true;
    }
    void rollBack(int stkSz){
        while (sk.size()>stkSz){
            op operation=sk.top(); sk.pop();
            par[operation.v]=operation.parV;
            if(operation.u==-1) continue;
            sz[operation.u]=operation.szU;
            cnt=operation.cnt;
        }
    }
}dsu;
int q,ans[N];

struct node{
    vector<pair<int,int>> v;
    vector<int> query;
}seg[1<<20];
void addEdge(int qs,int qe,pair<int,int> e,int ni=0,int ns=0,int ne=q){
    if(qe<ns or qs>ne) return;
    if(ns>=qs and ne<=qe){
        if(e.first==-1)  seg[ni].query.push_back(e.second);
        else seg[ni].v.push_back(e);
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
    for (auto it:seg[ni].query){
        ans[it]=dsu.cnt;
    }
    if(ns!=ne){
        int lf=2*ni+1,rt=lf+1,mid=ns+(ne-ns)/2;
        dfs(lf,ns,mid);
        dfs(rt,mid+1,ne);
    }
    dsu.rollBack(sz);
}

int main(){
    freopen("connect.in","r",stdin);
    freopen("connect.out","w",stdout);
    int n,cnt=0,u,v;
    char ch;
    scanf("%d%d",&n,&q);
    dsu.init(n);
    map<pair<int,int> ,int> mp;
    for (int i = 0; i < q; ++i) {
        scanf(" %c", &ch);
        if (ch == '?') {
            addEdge(i, i, {-1, cnt++});

        } else {
            scanf("%d%d", &u, &v);
            --u, --v;
            if (u > v) swap(u, v);
            if (ch == '+') {
                mp[{u, v}] = i;
            } else {
                addEdge(mp[{u, v}], i, {u, v});
                mp.erase({u, v});
            }
        }

    }
    for(auto it:mp){
        addEdge(it.second,q,it.first);
    }
    dfs();
    for (int i = 0; i < cnt; ++i) {
        printf("%d\n",ans[i]);
    }
}

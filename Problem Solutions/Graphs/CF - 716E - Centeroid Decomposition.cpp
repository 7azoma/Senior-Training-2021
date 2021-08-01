#include <bits/stdc++.h>
#include "ext/numeric"
using namespace __gnu_cxx;
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, M = 2 * N;
int tenInvPW[N];
int n,m;
int phi(int x){//complexity sqrt(x)
    int res=x;
    for(int i=2;i<=x/i;i++) {
        if (x % i) continue;
        res -= res / i;
        while (!(x % i)) {
            x /= i;
        }
    }
    if(x>1) res-=res/x;
    return res;
}
struct Mul{
    int m;
    Mul(int m):m(m){}
    int operator()(int a,int b){
        return (a*1ll*b)%m;
    }
};
int identity_element(const Mul&){
    return 1;
}
int mod_inverse(int x,int m){//x base , m power
    return power(x,phi(m)-1,Mul(m));
}
Mul mul(0);
struct ADJ {
    int head[N], nxt[M],cost[M], to[M], ne, n;
    void addEdge(int u, int v,int c) {
        nxt[ne] = head[u];
        to[ne] = v;
        cost[ne]=c;
        head[u] = ne++;
    }
    void addBiEdge(int u, int v,int c) {
        addEdge(u, v,c);
        addEdge(v, u,c);
    }
    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }
} adj;
#define neig(u, v, e, a) for(int e=a.head[u],v;~e and (v=a.to[e],1);e=a.nxt[e])

int treeCentroid,sz[N],treeSz,minChild,deleted[N],delId;
void calc_SZ(int u,int p){
    sz[u]=1;
    int mx=0;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==delId) continue;
        calc_SZ(v,u);
        sz[u]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,treeSz-sz[u]);
    if(mx<minChild) {
        minChild=mx;
        treeCentroid=u;
    }
}
int pre[N],Sz,suf[N],len[N];
void calc_paths(int u,int p,int prefix,int suffix,int len,int pw){
    pre[Sz]=prefix,suf[Sz]=suffix;
    ::len[Sz++]=len;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==delId) continue;
        calc_paths(v,u,(prefix+mul(adj.cost[e],pw))%m,(mul(suffix,10)+adj.cost[e])%m,len+1,mul(pw,10));
    }
}
ll solve(int u,int digit){
    Sz=0;
    calc_paths(u,-1,digit%m,digit%m,digit!=0,(digit!=0)?10:1);
    unordered_map<int,int > mp;
    for (int i = 0; i < Sz; ++i) {
        mp[pre[i]]++;
    }
    ll ret=0;
    for (int i = 0; i < Sz; ++i) {
       ret+= mp[ mul(m-suf[i],tenInvPW[len[i]]) ];
    }
    return ret;
}
ll decompose(int u){
    ll ret=solve(u,0)-1;
    deleted[u]=delId;
    neig(u,v,e,adj) {
        if (deleted[v] == delId) continue;
        ret -= solve(v, adj.cost[e]);
        treeSz = minChild = sz[v];
        calc_SZ(v,-1);
        calc_SZ(treeCentroid,-1);
        ret+=decompose(treeCentroid);
    }
    return ret;
}
ll centroid(){
    treeSz=minChild=adj.n;
    delId++;
    calc_SZ(0,-1);
    calc_SZ(treeCentroid,-1);
    return decompose(treeCentroid);
}

int main(){
//    freopen("in.txt","r",stdin);
   scanf("%d%d",&n,&m);
   int u,v,c;
   int tenInverse=mod_inverse(10,m);
   mul=Mul(m);
   adj.init(n);
   tenInvPW[0]=1;
    for (int i = 1; i < n; ++i) {
        tenInvPW[i]=mul(tenInvPW[i-1],tenInverse);
        scanf("%d%d%d",&u,&v,&c);
        adj.addBiEdge(u,v,c);
    }
    printf("%lld\n",centroid());
}



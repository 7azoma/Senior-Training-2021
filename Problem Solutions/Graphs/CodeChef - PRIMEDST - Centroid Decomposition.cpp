// https://www.codechef.com/problems/PRIMEDST
#include<bits/stdc++.h>

#define FAST ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
#define endl '\n'
typedef long long ll;
const int N = 5e4 + 10, M = 2 * N;

struct ADJ {
    int head[N], nxt[M], to[M], ne, n;
    void addEdge(int u, int v) {
        nxt[ne] = head[u];
        to[ne] = v;
        head[u] = ne++;
    }
    void addBiEdge(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }
} adj;

#define neig(u, v, e, a) for(int e=a.head[u],v;~e and (v=a.to[e],1);e=a.nxt[e])

int sz[N];
int deleted[N],deletedId;
void calcSz(int u,int p){
    sz[u]=1;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        calcSz(v,u);
        sz[u]+=sz[v];
    }
}
bool isComposite[N];
int primes[N],primesSz;
void seive() {
    isComposite[0] = isComposite[1] = 1;
    for (int p = 2; p < N; ++p) {
        if (!isComposite[p]) {
            primes[primesSz++] = p;
            for (ll i = 1ll * p * p; i < N; i += p)
                isComposite[i] = 1;
        }
    }
}
int distFreq[N];
ll count(int u,int p,int Sz,int d){
    ll ret=0;
    for (int i = 0; i < primesSz and primes[i]<=Sz; ++i) {
        int pr=primes[i];
        if(d>pr) continue;
        ret+=distFreq[pr-d];
    }
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        ret+=count(v,u,Sz,d+1);
    }
    return ret;
}
void add(int u,int p,int dis,int dir) {
   distFreq[dis]+=dir;
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        add(v,u,dis+1,dir);
    }
}
// return centeroid of tree
ll decompose(int u,int p,int s){
    neig(u,v,e,adj){
        if(v==p or deleted[v]==deletedId) continue;
        if(sz[v]*2 > s) return decompose(v,u,s);
    }
    deleted[u]=deletedId;
    distFreq[0]++;
    ll res=0;
    neig(u,v,e,adj) {
        if (deleted[v] == deletedId) continue;
        res+=count(v,u,s,1);
        add(v,u,1,1);
    }
    distFreq[0]--;
    neig(u,v,e,adj) {
        if (deleted[v] == deletedId) continue;
        add(v,u,1,-1);
    }
    neig(u,v,e,adj){
        if(deleted[v]==deletedId) continue;
        calcSz(v,u);
        res+=decompose(v,u,sz[v]);
    }
    return res;
}

ll centroid(int root){
    deletedId++;
    calcSz(root,-1);
    return decompose(root,-1,sz[root]);
}

ll init(){
   return centroid(0);
}

int main() {
    int n,u,v;
    scanf("%d",&n);
    adj.init(n);
    seive();
    for (int i = 1; i < n; ++i) {
        scanf("%d%d",&u,&v);
        --u,--v;
        adj.addBiEdge(u,v);
    }
    ll res=init(),all=n*(n-1ll)/2;
    printf("%.9lf\n",double(res)/all);
}

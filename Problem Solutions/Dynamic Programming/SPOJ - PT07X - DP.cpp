#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5, M = 2 * N;

struct ADJ {
    int nxt[M], head[N], to[M], ne, n;

    void init(int n) {
        this->n = n;
        ne = 0;
        memset(head, -1, n * sizeof head[0]);
    }

    void addEdge(int u, int v) {
        to[ne] = v;
        nxt[ne] = head[u];
        head[u] = ne++;
    }

    void addBiEdge(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
} adj;

#define nieg(a, u, v, e) for(int e = a.head[u],v;~e && (v=a.to[e],1);e=a.nxt[e])

int n;
int dp[N],vis[N],vid;

int solve(int u,int p){

    int &ret=dp[u];
    if(vis[u]==vid) return ret;
    vis[u]=vid;
    int c1=1,c2=0;
    nieg(adj,u,v,e){
        if(v==p) continue;
        c1+=solve(v,u);
        c2++;
        nieg(adj,v,w,e2){
            if(w==u) continue;
            c2+=solve(w,v);
        }
    }
    return ret=min(c1,c2);
}



int main(){
    scanf("%d",&n);
    adj.init(n);
    for (int i = 1; i < n; ++i) {
        int u,v;
        scanf("%d%d",&u,&v);
        adj.addBiEdge(--u,--v);
    }
    vid++;
    printf("%d\n",solve(0,-1));
}

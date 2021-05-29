#include <iostream>
using namespace std;

int main() {
	// your code goes here
	return 0;
}/**
 * Critical Links UVA - 796 
 * tarjan algorithm - undirected graph
 */

#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 5e4 + 5, M = 2 * N;

struct ADJ {
    int n, head[N], nxt[M], to[M], ne;

    void addEdge(int f, int t) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }

    void addBiEdge(int f, int t){
        addEdge(f,t);
        addEdge(t,f);
    }

    int addNode(){
        head[n]=-1;
        return n++;
    }
    void init(int n) {
        this->n=n;
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

} adj, comps;

int vis[N], vid, stk[N], stkSz,isArt[N],isBridge[M],lw[N],dfsTime[N], curTime;

void tarjanDFS(int u, int pe) {
    vis[u]=vid;
    stk[stkSz++]=u;
    lw[u]=dfsTime[u]=curTime++;
    for(int e=adj.head[u]; ~e; e=adj.nxt[e]){
        if(e==pe)continue;
        int v=adj.to[e];
        if(vis[v]!=vid){
            tarjanDFS(v,e^1);
            lw[u]=min(lw[u],lw[v]);
            if(lw[v]>=dfsTime[u]){
                if(~pe || dfsTime[v]>dfsTime[u]+1)isArt[u]=vid;
                int id=comps.addNode();
                comps.addEdge(id,u);
                do {
                    comps.addEdge(id,stk[--stkSz]);
                }while (stk[stkSz]!=v);

            }
            if(lw[v]>dfsTime[u]) {
                isBridge[e]=isBridge[e^1]=vid;
            }

        }else{
            lw[u]=min(lw[u],dfsTime[v]);

        }
    }
}

void T() {
    comps.init(0);
    ++vid;
    curTime=0;
    for (int i = 0; i < adj.n; ++i)
        if(vis[i]!=vid){
            stkSz=0;
            tarjanDFS(i,-1);
            if(!(~adj.head[i]))comps.addEdge(comps.addNode(),i);
        }


}



int main() {int n,m, q;
//    freopen("auth.txt","r",stdin);
    while(~scanf("%d",&n)){
        adj.init(n);
        while (n--){
            int u;
            scanf("%d (%d)",&u,&m);
            while (m--){
                int v;
                scanf("%d",&v);
                if(u<v)
                adj.addBiEdge(u,v);
            }
        }
        T();
        vector<pair<int,int> >vec;
        for (int i = 0; i < adj.ne; i+=2) {
            if(isBridge[i]==vid){
                vec.emplace_back(adj.to[i],adj.to[i^1]);
                if(vec.back().first> vec.back().second)swap(vec.back().first,vec.back().second);
            }
        }
        printf("%d critical links\n",vec.size());
        sort(vec.begin(),vec.end());
        for(auto e:vec){
            printf("%d - %d\n",e.first, e.second);
        }
        puts("");
    }
    return 0;
}

#include <bits/stdc++.h>


#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 4 * N +9;

struct ADJ {
    int head[N], nxt[M], to[M], ne,n;
    void addEdge(int f, int t) {
        nxt[ne] = head[f];
        to[ne] = t;
        head[f] = ne++;
    }
    void init(int n) {
        this->n=n;
        memset(head, -1, n * sizeof head[0]);
        ne = 0;
    }

} adj, Cgraph;

int vis[N], vid, stk[N], stkSz, compId[N], ncp,lw[N],dfsTime[N], curTime;

void tarjanDFS(int u){
    vis[u]=vid;
    stk[stkSz++]=u;
    lw[u]=dfsTime[u]=curTime++;
    compId[u]=-1;
    for(int e=adj.head[u]; ~e ; e=adj.nxt[e]){
        int v=adj.to[e];
        if(vis[v]!=vid){
            tarjanDFS(v); ///white
            lw[u]=min(lw[u],lw[v]);
        } else if(compId[v]==-1){ // Gray
            lw[u]=min(lw[u],lw[v]);
        }
    }

    if(lw[u]==dfsTime[u]){
        do{
            compId[stk[--stkSz]]=ncp;
        }while (stk[stkSz]!=u);

        ncp++;
    }

}

int notSrc[N], notSnk[N];
int compVal[N];

void dfs(int u){
    if(vis[u]==vid)return;
    vis[u]=vid;
    for(int e=adj.head[u]; ~e; e=adj.nxt[e]){
        int v= adj.to[e];
        dfs(v);
    }
    if(!~compVal[compId[u]]){
        compVal[compId[u]]=1;
        compVal[compId[u^1]]=0;
    }
}
void getSol(){
    vid++;
    memset(compVal,-1,sizeof(compVal[0])*ncp);
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid){
            dfs(i);
        }
    }
}
void T() {
    ++vid;
    ncp=0;
    curTime=0;
    for (int i = 0; i < adj.n; ++i)
        if (vis[i] != vid)
            tarjanDFS(i);

    Cgraph.init(ncp);
    for (int u = 0; u < adj.n; ++u) {
        for (int e = adj.head[u]; ~e; e = adj.nxt[e]) {
            int v = adj.to[e];
            if (compId[u] == compId[v]) continue; //intera comp edge
            Cgraph.addEdge(compId[u], compId[v]);
            notSnk[compId[u]] = vid;
            notSrc[compId[v]] = vid;
        }
    }
}
#define Var(x) ((x)<<1)
#define H(x) ((x)<<1)
#define W(x) (((x)<<1)+1)
#define Not(x) ((x)^1)

void addOR(int a,int b){
    adj.addEdge(Not(a),b);
    adj.addEdge(Not(b),a);
}

void addXOR(int a,int b){
    addOR(a,b);
    addOR(Not(a),Not(b));
}


void addXNOR(int a,int b){
    addOR(Not(a),b);
    addOR(a,Not(b));
}
int getID(char c,int v){
    return c=='h'?H(v):W(v);
}
bool noSol(){
    for(int i=0;i<adj.n;i+=2){
        if(compId[i]==compId[i^1]){
            return 1;
        }
    }
    return 0;
}
int m, q;
int state[N];
int main() {

    int n;
    while(~scanf("%d%d",&n,&m), n || m){
        adj.init(4*n);
        addOR(Var(W(0)),Var(W(0)));

        for(int i=0;i<m;i++){
            char c1,c2;
            int a,b;
            scanf(" %d%c %d%c",&a,&c1,&b,&c2);
            int id1=getID(c1,a);
            int id2=getID(c2,b);

            addOR(Var(id1),Var(id2));

        }
        for(int i=0;i<n;i++){
            int id1=getID('h',i);
            int id2=getID('w',i);
            addXOR(Var(id1),Var(id2));
        }

        T();

        if(noSol()){
            puts("bad luck");
        }else{
            getSol();
            for(int i=1;i<n;i++){
                int hId=Var(H(i));
                if(compVal[compId[hId]]){
                    printf("%dh",i);
                }else{
                    printf("%dw",i);
                }
                printf("%c"," \n"[i+1==n]);
            }
        }
    fflush(stdout);
    }


    return 0;
}

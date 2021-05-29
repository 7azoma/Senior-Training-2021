// https://www.spoj.com/problems/COT2/en/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5 + 2;

int freq[N], qs[N], qe[N], qi[N], qAns[N], qLca[N], n, q, sq, s, e, ans;

// lca data
int nodeToIndex[N], indexToNode[N], dfn, depth[N];
// node data
int stTime[N], enTime[N], curTime, timeToNode[N];
// graph adj
int to[N], head[N], nxt[N], ne;
ll nodeVal[N], sortNodeVal[N];

void dfs(int u, int par){
    indexToNode[nodeToIndex[u] = dfn++] = u;
    timeToNode[stTime[u] = curTime++] = u;
    for (int e = head[u]; ~e; e = nxt[e]){
        int v = to[e];
        if (v == par) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        indexToNode[dfn++] = u;
    }
    timeToNode[enTime[u] = curTime++] = u;
}

int sp[18][N], lg[N];
void buildSP(){
    lg[0] = -1;
    for (int i = 0; i < dfn; ++i){
        lg[i + 1] = lg[i] + !(i & (i + 1));
        sp[0][i] = i;
    }
    for (int j = 1; (1 << j) <= dfn; ++j){
        for (int i = 0; i + (1 << j) <= dfn; ++i){
            int a = sp[j - 1][i], b = sp[j - 1][i + (1 << (j - 1))];
            sp[j][i] = (depth[indexToNode[a]] < depth[indexToNode[b]] ? a : b);
        }
    }
}
int RMQ(int a, int b){
    int Log = lg[b - a + 1];
    a = sp[Log][a];
    b = sp[Log][b - (1 << Log) + 1];
    return (depth[indexToNode[a]] < depth[indexToNode[b]] ? a : b);
}
int LCA(int u, int v){
    u = nodeToIndex[u];
    v = nodeToIndex[v];
    if (u > v) swap(u, v);
    return indexToNode[RMQ(u, v)];
}

void init(){
    memset(head + 1, -1, sizeof(head[0]) * n); ne = 0;
}
void addEdge(int f, int t){
    to[ne] = t;
    nxt[ne] = head[f];
    head[f] = ne++;
}
void addBiEdge(int u, int v){
    addEdge(u, v);
    addEdge(v, u);
}


bool isOdd[N];
void add(int val){
    ans += !freq[val]++;
}
void del(int val){
    ans -= !--freq[val];
}

void flip(int i){
    int u = timeToNode[i];
    if (isOdd[u] ^= 1){
        add(nodeVal[u]);
    }
    else{
        del(nodeVal[u]);
    }
}

void updateSE(int idx){
    while (e < qe[idx] + 1) flip(e++);
    while (s > qs[idx]) flip(--s);
    while (s < qs[idx]) flip(s++);
    while (e > qe[idx] + 1) flip(--e);
}

void arrPrint(int a[], int sz){
    for ( int i = 0; i < sz; ++i ){
        printf("%d%c", a[i], " \n"[i + 1 == sz]);
    }
}

int main(){
#ifdef CLion
    freopen("input.txt" , "r" , stdin);
#endif

    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i){
        scanf("%d", nodeVal + i);
        sortNodeVal[i] = nodeVal[i];
    }

    sort(sortNodeVal + 1, sortNodeVal + n + 1);
    int un = unique(sortNodeVal, sortNodeVal + n + 1) - sortNodeVal;
    for (int i = 1; i <= n; ++i){
        nodeVal[i] = lower_bound(sortNodeVal, sortNodeVal + un, nodeVal[i]) - sortNodeVal;
    }

    init();
    for ( int i = 1; i < n; ++i ){
        int u, v;
        scanf("%d%d", &u, &v);
        addBiEdge(u, v);
    }
    dfs(1, 1);
    buildSP();


    for ( int i = 0; i < q; ++i ){
        int u, v;
        scanf("%d%d", &u, &v);
        if (stTime[u] > stTime[v]) {
            swap(u, v);
        }
        int lca = LCA(u, v);
        qLca[i] = lca;

        qi[i] = i;
        if (u == lca){
            qs[i] = stTime[u] + 1;
            qe[i] = stTime[v];
        }
        else{
            qs[i] = enTime[u];
            qe[i] = stTime[v];
        }

//        printf("%d %d\n", qs[i], qe[i]);
    }


    sq = sqrt(curTime);
//    printf("%d\n", sq);
    sort(qi, qi + q, [](int a, int b){
        return make_pair(qs[a] / sq, qe[a]) < make_pair(qs[b] / sq, qe[b]);
    });

//    arrPrint(indexToNode, dfn);
//    arrPrint(timeToNode, curTime);

    /*
     *
     *      1 4 8 8 4 3 7 7 6 6 5 5 3 2 2 1
     *
     *
     */

    for ( int i = 0; i < q; ++i ){
        int cur = qi[i];
        updateSE(cur);
        add(nodeVal[qLca[cur]]);
        qAns[cur] = ans;
        del(nodeVal[qLca[cur]]);
    }
    for (int i = 0; i < q; ++i){
        printf("%d\n", qAns[i]);
    }



//    for ( int i = 1; i <= n; ++i ){
//        for ( int j = i + 1; j <= n; ++j ){
//            printf("%d %d %d\n", i, j, LCA(i, j));
//        }
//    }

    return 0;
}
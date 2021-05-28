//#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int nodeData;

const int MaxNodes = 2e5 + 2;

extern struct node nodes[MaxNodes];

enum DIR {LF, RI};
struct node{
    bool isRev;
    nodeData val;
    int par, Sz, ch[2];

    void set(nodeData nodeValue){
        ch[0] = ch[1] = par = 0;
        val = nodeValue;
        Sz = 1;
    }

    void push_up(){
        Sz = 1 + nodes[ch[LF]].Sz + nodes[ch[RI]].Sz;
    }
    void push_down(){
        if (isRev){
            for (int i = 0; i < 2; ++i){
                if (ch[i]){
                    nodes[ ch[i] ].reverse();
                }
            }
            isRev = 0;
        }
    }
    void reverse(){
        swap(ch[LF], ch[RI]);
        isRev ^= 1;
    }
}nodes[MaxNodes];

int freeList[MaxNodes], freeListSz, nextNodeId;

int getFreeNodeId(){
    if (freeListSz){
        return freeList[--freeListSz];
    }
    return nextNodeId++;
}
void init(){
    nextNodeId = 1;
    freeListSz = 0;
}
void makeFree(int nodeId){
    freeList[freeListSz++] = nodeId;
}

void link(int par, int child, DIR d){
    if (par){
        nodes[par].ch[d] = child;
        nodes[par].push_up();
    }
    if (child){
        nodes[child].par = par;
    }
}
DIR getDir(int par, int child){
    return (DIR)(nodes[par].ch[RI] == child);
}
/*
 *         gp
 *         |
 *         |
 *         p
 *       d/ \
 *       a  q
 *         / \
 *        b   c
 */
void rotate(int p, DIR d){
    int gp = nodes[p].par;
    int q = nodes[p].ch[!d];
    link(p, nodes[q].ch[d], (DIR)(!d));
    link(q, p, d);
    link(gp, q, getDir(gp, p));
}
/*
 *         gp
 *         |
 *         |
 *         q
 *        / \
 *      p    c
 *     / \
 *   a    b
 */



/*
 *       gp
 *   gpd/ \
 *     p
 *    / \pd
 *     nodeid
 */
void splay(int nodeId, int &root){
    while (nodes[nodeId].par){
        int p = nodes[nodeId].par;
        int gp = nodes[p].par;
        int pd = getDir(p, nodeId);
        int gpd = getDir(gp, p);

        if (!gp){
            rotate(p, (DIR)(!pd));
        }
        else if (pd == gpd){
            rotate(gp, (DIR)(!gpd));
            rotate(p, (DIR)(!gpd));
        }
        else{
            rotate(p, (DIR)(!pd));
            rotate(gp, (DIR)(!gpd));
        }
    }
    root = nodeId;
}

nodeData getByIdx(int &root, int index){
    int cur = root;

    while (nodes[cur].push_down(), nodes[ nodes[cur].ch[LF] ].Sz > index or index >= nodes[ nodes[cur].ch[LF] ].Sz + 1){
        if ( nodes[ nodes[cur].ch[LF] ].Sz > index ){
            cur = nodes[cur].ch[LF];
        }
        else{
            index -= nodes[ nodes[cur].ch[LF] ].Sz + 1;
            cur = nodes[cur].ch[RI];
        }
    }

    splay(cur, root);
    return nodes[cur].val;
}

void splayMax(int &root){
    int cur ;
    for (cur = root; nodes[cur].push_down(), nodes[cur].ch[RI]; cur = nodes[cur].ch[RI]);
    splay(cur, root);
}

int merge(int ls, int gr){
    if (!ls) return gr;
    splayMax(ls);
    link(ls, gr, RI);
    return ls;
}

void split(int root, int lfSz, int &ls, int &gr){
    if (lfSz >= nodes[root].Sz){
        ls = root;
        gr = 0;
        return void();
    }
    getByIdx(root, lfSz);
    ls = nodes[root].ch[LF];
    link(root, 0, LF);
    link(0, ls, LF);
    gr = root;
}

void print(int node, int depth){
    if (!node){
        return void();
    }
    print(nodes[node].ch[LF], depth + 1);
    printf("%s%d\n", string(depth, ' ').c_str(), nodes[node].val);
    print(nodes[node].ch[RI], depth + 1);
}

void print(int node){
    puts("--------------");
    print(node, 0);
    puts("--------------");
    fflush(stdout);
}

void pushDownFromRoot(int node) {
    if (!node) return;
    pushDownFromRoot(nodes[node].par);
    nodes[node].push_down();
}

int getIdx(int cur) {
    pushDownFromRoot(cur);
    int ret = nodes[ nodes[cur].ch[LF] ].Sz;
    while (cur) {
        int p = nodes[cur].par;
        if (getDir(p, cur) == RI)
            ret += nodes[ nodes[p].ch[LF] ].Sz + 1;
        cur = p;
    }
    return ret;
}

void reverse(int &cur, int st, int en) {
    int bef, aft, btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);
    nodes[ btwn ].reverse();
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}

int main(){
#ifdef CLion
    freopen("input.txt" , "r" , stdin);
#endif


    int n;
    while (scanf("%d", &n), n) {
        init();
        int root = 0;

        vector<int> V;
        int x;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            int Node = getFreeNodeId();
            nodes[Node].set(x);

            V.emplace_back(Node);
            root = merge(root,V.back());
        }
        stable_sort(V.begin(), V.end(), [](int a, int b) {
            return nodes[a].val < nodes[b].val;
        });
        int i = 0;
        for(auto &nod : V){
            int idx = getIdx(nod);
            printf("%d%c",idx+1," \n"[&nod==&V.back()]);
            reverse(root,i++,idx);
        }
    }
    return 0;
}

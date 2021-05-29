#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int nodeData;

const int MaxNodes = 2e5 + 2, N = MaxNodes;

extern struct node nodes[MaxNodes];

enum DIR {LF, RI};
struct node{
    nodeData val;
    int freq, par, Sz, ch[2];

    void set(nodeData nodeValue){
        ch[0] = ch[1] = par = 0;
        val = nodeValue;
        freq = Sz = 1;
    }

    void push_up(){
        Sz = freq + nodes[ch[LF]].Sz + nodes[ch[RI]].Sz;
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
inline void rotate(int q) {
    int p = nodes[q].par;
    DIR d = getDir(p, q);
    int gp = nodes[p].par;
    // p -> q -> gp
    link(p, nodes[q].ch[!d], d);
    link(q, p, (DIR)!d);
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
inline void splay(int nodeId, int &root) {
    int p;
    while(p = nodes[nodeId].par)
    {
        int gp = nodes[p].par;
        if(!gp) rotate(nodeId);
        else
        {
            rotate(getDir(gp, p) == getDir(p, nodeId) ? p : nodeId);
            rotate(nodeId);
        }
    }
    root = nodeId;
}

void getNodeAt(nodeData value, int &root){
    while (value != nodes[root].val){
        if (value < nodes[root].val){
            if (nodes[root].ch[LF]){
                root = nodes[root].ch[LF];
            }
            else{
                break;
            }
        }
        else{
            if (nodes[root].ch[RI]){
                root = nodes[root].ch[RI];
            }
            else{
                break;
            }
        }
    }
    splay(root, root);
}

void insert(int &root, nodeData value){
    if (!root) {
        root = getFreeNodeId();
        nodes[root].set(value);
        return void();
    }

    getNodeAt(value, root);
    if (nodes[root].val == value){
        nodes[root].freq++;
        nodes[root].Sz++;
    }
    else{
        DIR d = (DIR)(value > nodes[root].val);
        int id = getFreeNodeId();
        nodes[id].set(value);
        link(id, nodes[root].ch[d], d);
        link(root, 0, d);
        link(id, root, (DIR)(!d));
        root = id;
    }
}

int lb(int &root, nodeData value){
    if (!root){
        return 0;
    }

    int ret = 0, cur;
    for (cur = root; nodes[cur].val != value; ){
        DIR d = (DIR)(value > nodes[cur].val);

        if (d){
            ret += nodes[ nodes[cur].ch[LF] ].Sz + nodes[cur].freq;
        }

        if (nodes[cur].ch[d]){
            cur = nodes[cur].ch[d];
        }
        else break;
    }
    if (value == nodes[cur].val){
        ret += nodes[ nodes[cur].ch[LF] ].Sz;
    }
    splay(cur, root);
    return ret;
}
int ub(int &root, nodeData value){
    return lb(root, value + 1);
}

nodeData getByIdx(int &root, int index){
    if (index >= nodes[root].Sz){
        return INT_MIN;
    }

    int cur = root;
    while (nodes[ nodes[cur].ch[LF] ].Sz > index or index >= nodes[ nodes[cur].ch[LF] ].Sz + nodes[cur].freq){
        if ( nodes[ nodes[cur].ch[LF] ].Sz > index ){
            cur = nodes[cur].ch[LF];
        }
        else{
            index -= nodes[ nodes[cur].ch[LF] ].Sz + nodes[cur].freq;
            cur = nodes[cur].ch[RI];
        }
    }

    splay(cur, root);
    return nodes[cur].val;
}

void splayMax(int &root){
    int cur ;
    for (cur = root; nodes[cur].ch[RI]; cur = nodes[cur].ch[RI]);
    splay(cur, root);
}

int merge(int ls, int gr){
    if (!ls) return gr;
    splayMax(ls);
    link(ls, gr, RI);
    return ls;
}

void del(int &root, nodeData value){
    getNodeAt(value, root);
    if (value == nodes[root].val){
        if (nodes[root].freq > 1){
            --nodes[root].freq;
            --nodes[root].Sz;
        }
        else{
            makeFree(root);
            link(0, nodes[root].ch[LF], LF);
            link(0, nodes[root].ch[RI], LF);
            root = merge(nodes[root].ch[LF], nodes[root].ch[RI]);
        }
    }
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

int arr[N];
unordered_map<int, int> roots;

int main(){
    init();
    int n, q;
    scanf("%d%d", &n, &q);
    roots.reserve(n);
    for(int i = 0 ; i < n ; i++)
    {
        scanf("%d", arr + i);
        insert(roots[arr[i]], i);
    }
    int idx, x;
    for(int i = 0 ; i < q ; i++)
    {
        scanf("%d%d", &idx, &x);
        del(roots[arr[idx]], idx);
        insert(roots[arr[idx] = x], idx);
        printf("%d\n", lb(roots[arr[idx]], idx));
    }
    return 0;
}
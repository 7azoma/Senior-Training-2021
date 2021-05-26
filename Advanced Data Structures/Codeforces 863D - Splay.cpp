#pragma GCC optimize ("O3")

#include <cstdio>
#include <cstring>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;
typedef int ll;
typedef ll nodeData;

const int MaxNodes = 2e5 + 2;
extern struct node nodes[MaxNodes];

enum DIR {
    LF, RI
};

struct node {
    nodeData val, lzAdd, mn;
    bool isRev;
    int par, Sz, ch[2];
    node(){
        memset(this,0,sizeof *this);
        mn=INT_MAX;
    }
    void set(nodeData nodeValue) {
        ch[0] = ch[1] = par = 0;
        mn= val = nodeValue;
        lzAdd=0;
        isRev=0;
        Sz = 1;
    }

    void push_up() {
        Sz = 1 + nodes[ch[LF]].Sz + nodes[ch[RI]].Sz;
        mn = min(val, min(nodes[ch[LF]].mn, nodes[ch[RI]].mn));
    }

    void add_lazy(nodeData lazyValue) {
        if (this == &nodes[0]) {
            return void();
        }
        lzAdd += lazyValue;
        val += lazyValue;
        mn += lazyValue;
    }

    void push_down() {
        if (isRev) {
            for (int i = 0; i < 2; ++i) {
                if (ch[i]) {
                    nodes[ch[i]].reverse();
                }
            }
            isRev = 0;
        }
        if (lzAdd) {
            for (int i = 0; i < 2; ++i) {
                if (ch[i]) {
                    nodes[ch[i]].add_lazy(lzAdd);
                }
            }
            lzAdd = 0;
        }
    }

    void reverse() {
        swap(ch[LF], ch[RI]);
        isRev ^= 1;
    }
} nodes[MaxNodes];

int freeList[MaxNodes], freeListSz, nextNodeId;

inline int getFreeNodeId() {
    if (freeListSz) {
        return freeList[--freeListSz];
    }
    return nextNodeId++;
}

inline void init() {
    nextNodeId = 1;
    freeListSz = 0;
}

inline void makeFree(int nodeId) {
    freeList[freeListSz++] = nodeId;
}

inline void link(int par, int child, DIR d) {
    if (par) {
        nodes[par].ch[d] = child;
        nodes[par].push_up();
    }
    if (child) {
        nodes[child].par = par;
    }
}

inline DIR getDir(int par, int child) {
    return (DIR) (nodes[par].ch[RI] == child);
}

/*
 *         gp
 *         |
 *         |
 *         p
 *        / \d
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

inline nodeData getByIdx(int &root, int index) {
    int cur = root,lftsz;

    while (nodes[cur].push_down(),lftsz=nodes[nodes[cur].ch[LF]].Sz, lftsz > index or index >= lftsz+ 1) {
        if (lftsz > index) {
            cur = nodes[cur].ch[LF];
        } else {
            index -= lftsz + 1;
            cur = nodes[cur].ch[RI];
        }
    }

    splay(cur, root);
    return nodes[cur].val;
}

inline void splayMax(int &root) {
    int cur;
    for (cur = root; nodes[cur].push_down(), nodes[cur].ch[RI]; cur = nodes[cur].ch[RI]);
    splay(cur, root);
}

inline int merge(int ls, int gr) {
    if (!ls) return gr;
    splayMax(ls);
    link(ls, gr, RI);
    return ls;
}

inline void split(int root, int lfSz, int &ls, int &gr) {
    if (lfSz >= nodes[root].Sz) {
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

inline void print(int node, int depth) {
    if (!node) {
        return void();
    }
    print(nodes[node].ch[LF], depth + 1);
    printf("%s(%2d,%2d)\n", string(7 * depth, ' ').c_str(), nodes[node].val, nodes[node].mn);
    print(nodes[node].ch[RI], depth + 1);
}

inline void print(int node) {
    puts("--------------");
    print(node, 0);
    puts("--------------");
    fflush(stdout);
}

inline void pushDownFromRoot(int node) {
    if (!node) return;
    pushDownFromRoot(nodes[node].par);
    nodes[node].push_down();
}

inline int getIdx(int cur) {
    pushDownFromRoot(cur);
    int ret = nodes[nodes[cur].ch[LF]].Sz;
    while (cur) {
        int p = nodes[cur].par;
        if (getDir(p, cur) == RI)
            ret += nodes[nodes[p].ch[LF]].Sz + 1;
        cur = p;
    }
    return ret;
}

inline void insert(int &cur, int pos, nodeData val) {
    int bef, aft, btwn;
    split(cur, pos, bef, aft);
    btwn = getFreeNodeId();
    nodes[btwn].set(val);
    //nodes[aft].add_lazy(1);
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}


inline void del(int &cur, int pos) {
    int bef, aft, btwn;
    split(cur, pos + 1, cur, aft);
    split(cur, pos, bef, btwn);
    makeFree(btwn);
    // nodes[aft].add_lazy(-1);
    cur = merge(bef, aft);
}

inline void fastscan(ll &number) {
    //variable to indicate sign of input number
    bool negative = false;
    register int c;

    number = 0;

    // extract current character from buffer

    while (c = getchar(), isspace(c));
    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = (number << 3) + (number << 1) + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number = -number;
}




inline void reverse(int &cur, int st, int en) {
    int bef, aft, btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);
    nodes[btwn].reverse();
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}

inline void add(int &cur, int st, int en, nodeData val) {
    int bef, aft, btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);
    nodes[btwn].add_lazy(val);
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}


inline nodeData mn(int &cur, int st, int en) {
    int bef, aft, btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);
    nodeData ret = nodes[btwn].mn;
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
    return ret;
}

inline void rot(int &cur, int st, int en, int sh) {
    int bef, aft, btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);

    int pre, suf;
    split(btwn, nodes[btwn].Sz - sh, pre, suf);
    btwn = merge(suf, pre);

    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}
inline void fastscan(char str[]) {

    register int c;
    while (c = getchar(), isspace(c));
    int len = 0;
    do str[len++] = c; while (c = getchar(), !isspace(c));
    str[len] = 0;
}
int main() {
    init();
    int root = 0;
    int n, m, q, x, y;
    fastscan(n);
    fastscan(q);
    fastscan(m);
    for(int i = 0 ; i < n ; i++)
    {
        fastscan(x);
        y = getFreeNodeId();
        nodes[y].set(x);
        root = merge(root, y);
    }
    int typ, l, r;
    while(q--)
    {
        fastscan(typ);
        fastscan(l);
        fastscan(r);
        --l, --r;
        if(typ == 1)
        {
            rot(root, l, r, 1);
        }
        else
        {
            reverse(root, l, r);
        }
    }
    while(m--)
    {
        fastscan(x);
        --x;
        printf("%d%c", getByIdx(root, x), " \n"[!m]);
    }
    return 0;
}
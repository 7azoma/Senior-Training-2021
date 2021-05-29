//https://v...content-available-to-author-only...e.net/problem/SPOJ-CERC07S//#pragma GCC optimize ("O3")

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
extern struct node *EMPTY;
typedef int vTyp;
mt19937 eng{std::random_device{}()};
uniform_int_distribution<int> uid(0, (int) 2e9);

struct node {
    vTyp val;
    int pr, sz;
    node *ch[2], *par;
    bool rev;

    node() : ch({this, this}), par(this), sz(0), pr(INT_MIN), rev(false) {

    }

    node(vTyp val, int pr = rand()) : ch({EMPTY, EMPTY}), par(EMPTY), sz(1), pr(pr), val(val), rev(false) {

    }

    void reverse() {
        if (this == EMPTY) return;
        swap(ch[0], ch[1]);
        rev ^= 1;
    }
};

node *EMPTY = new node();
enum Dir {
    LF, RT
};

void push_up(node *cur) {
    cur->sz = 1 + cur->ch[LF]->sz + cur->ch[RT]->sz;
}

void link(node *pr, node *child, Dir dir) {
    if (child != EMPTY)
        child->par = pr;
    if (pr != EMPTY) {
        pr->ch[dir] = child;
        push_up(pr);
    }
}

void push_down(node *&cur) {
    if (cur == EMPTY || !cur->rev) return;
    cur->ch[LF]->reverse();
    cur->ch[RT]->reverse();
    cur->rev = 0;
}

Dir getDir(node *pr, node *child) {
    return (Dir) (pr->ch[RT] == child);
}

void print(node *root, int dp) {
    if (root == EMPTY) return;
    print(root->ch[LF], dp + 1);
    printf("%s(%d,%c)\n", string(5 * dp, ' ').c_str(), root->sz, root->val);
    print(root->ch[RT], dp + 1);
}

node *getByIdx(node *root, int idx) {
    if (root == EMPTY) return EMPTY;
    if (root->ch[LF]->sz > idx)
        return getByIdx(root->ch[LF], idx);
    int tmp = root->ch[LF]->sz + 1;
    if (tmp <= idx)
        return getByIdx(root->ch[RT], idx - tmp);
    return root;
}

void split(node *cur, int sz, node *&les, node *&grt) {
    if (cur == EMPTY) {
        les = grt = EMPTY;
        return;
    }
    push_down(cur);
    node *tmp;
    if (sz <= cur->ch[LF]->sz) {
        grt = cur;
        split(cur->ch[LF], sz, les, tmp);
        link(cur, tmp, LF);
    } else {
        les = cur;
        split(cur->ch[RT], sz - cur->ch[LF]->sz - 1, tmp, grt);
        link(cur, tmp, RT);
    }

}

void print(node *root) {
    print(root, 0);
    puts("-------------");
    fflush(stdout);
}

node *merge(node *les, node *grt) {

    if (les == EMPTY)
        return grt;
    if (grt == EMPTY)
        return les;
    push_down(grt);
    push_down(les);

    node *cur;
    if (les->pr > grt->pr) {
        cur = les;
        link(cur, merge(cur->ch[RT], grt), RT);
    } else {
        cur = grt;
        link(cur, merge(les, cur->ch[LF]), LF);
    }
    return cur;
}

void pushDownFromRoot(node *cur) {
    if (cur == EMPTY) return;
    pushDownFromRoot(cur->par);
    push_down(cur);
}

int getIdx(node *cur) {
    pushDownFromRoot(cur);
    int ret = cur->ch[LF]->sz;
    while (cur->par != EMPTY) {
        auto p = cur->par;
        if (getDir(p, cur) == RT)
            ret += p->ch[LF]->sz + 1;
        cur = p;
    }
    return ret;
}

void reverse(node *&cur, int st, int en) {
    node *bef, *aft, *btwn;
    split(cur, en + 1, cur, aft);
    split(cur, st, bef, btwn);
    btwn->reverse();
    cur = merge(btwn, aft);
    cur = merge(bef, cur);
}


int n;

int main() {
    node *root = EMPTY;
    while (scanf("%d", &n), n) {
        root = EMPTY;
        vector<node *> V;
        int x;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            V.emplace_back(new node(x));
            root = merge(root,V.back());
        }
        stable_sort(V.begin(), V.end(), [](node *a, node *b) {
            return a->val < b->val;
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
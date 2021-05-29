//https://v...content-available-to-author-only...e.net/problem/SPOJ-KPMATRIX
#pragma GCC optimize ("O3")

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
extern struct node *EMPTY;
typedef long long vTyp;
mt19937 eng{std::random_device{}()};
uniform_int_distribution<int> uid(0, (int) 2e9);

struct node {
    vTyp val;
    int pr, sz, frq;
    node *ch[2], *par;

    node() : ch({this, this}), par(this), frq(0), sz(0), pr(INT_MIN) {

    }

    node(vTyp val) : ch({EMPTY, EMPTY}), par(EMPTY), frq(1), sz(1), pr(rand()), val(val) {

    }

};

node *EMPTY = new node();
enum Dir {
    LF, RT
};

void push_up(node *cur) {
    cur->sz = cur->frq + cur->ch[LF]->sz + cur->ch[RT]->sz;
}

void link(node *pr, node *child, Dir dir) {
    if (child != EMPTY)
        child->par = pr;
    if (pr != EMPTY) {
        pr->ch[dir] = child;
        push_up(pr);
    }
}

Dir getDir(node *pr, node *child) {
    return (Dir) (pr->ch[RT] == child);
}

void rotate(node *&p, Dir d) {
    node *pp = p->par, *q = p->ch[!d];
    link(p, q->ch[d], (Dir) !d);
    link(q, p, d);
    link(pp, q, getDir(pp, p));
    p = q;
}

void print(node *root, int dp = 0) {
    if (root == EMPTY) return;
    print(root->ch[LF], dp + 1);
    printf("%s(%d,%3d)\n", string(3 * dp, ' ').c_str(), root->sz, root->val);
    print(root->ch[RT], dp + 1);
}

void balance(node *&cur) {
    if (cur->ch[RT]->pr > cur->pr)
        rotate(cur, LF);
    if (cur->ch[LF]->pr > cur->pr)
        rotate(cur, RT);
}

void insert(node *&cur, vTyp val) {
    if (cur == EMPTY)
        cur = new node(val);
    else if (cur->val == val)
        cur->frq++, cur->sz++;
    else if (val < cur->val)
        insert(cur->ch[LF], val);
    else
        insert(cur->ch[RT], val);
    push_up(cur);
    balance(cur);
}

node *remv_node(node *cur) {
    for (int d = 0; d < 2; ++d) {
        if (cur->ch[d] == EMPTY) {
            auto toDel = cur;
            link(cur->par, cur->ch[!d], getDir(cur->par, cur));
            cur = cur->ch[!d];
            delete toDel;
            return cur;
        }
    }
    if (cur->ch[LF]->pr > cur->ch[RT]->pr)
        rotate(cur, RT), cur->ch[RT] = remv_node(cur->ch[RT]);
    else
        rotate(cur, LF), cur->ch[LF] = remv_node(cur->ch[LF]);
    return cur;
}

void del(node *&root, vTyp val) {
    if (root == EMPTY) return;
    if (root->val == val) {
        if (!--root->frq) {
            root = remv_node(root);
        }
    } else if (root->val > val)
        del(root->ch[LF], val);
    else
        del(root->ch[RT], val);
    push_up(root);

}

int getByIdx(node *root, int idx) {
    if (root == EMPTY) return INT_MIN;
    if (root->ch[LF]->sz > idx)
        return getByIdx(root->ch[LF], idx);
    int tmp = root->ch[LF]->sz + root->frq;
    if (tmp <= idx)
        return getByIdx(root->ch[RT], idx - tmp);
    return root->val;
}

int lower_bound(node *root, vTyp val) {
    if (root == EMPTY)return 0;
    if (val == root->val)
        return root->ch[LF]->sz;
    if (val < root->val)
        return lower_bound(root->ch[LF], val);
    int tmp = root->ch[LF]->sz + root->frq;
    return tmp + lower_bound(root->ch[RT], val);
}

int upper_bound(node *root, vTyp val) {
    return lower_bound(root, val + 1);
}

int count(node *root, vTyp val) {
    if (root == EMPTY) return 0;
    if (root->val == val) return root->frq;
    if (val < root->val)
        return count(root->ch[LF], val);
    return count(root->ch[RT], val);
}

const int N = 260;
int q;
ll A[N][N];
int n, m, a, b;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%lld", &A[i][j]), A[i][j] += A[i][j - 1];
    scanf("%d%d", &a, &b);
    ll res = 0;
    for (int lf = 0; lf < m; lf++)
        for (int rt = lf + 1; rt <= m; ++rt) {
            node *root = EMPTY;
            insert(root, 0);
            ll sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += A[i][rt] - A[i][lf];
                res += upper_bound(root, sum - a) - lower_bound(root, sum - b);
                insert(root, sum);
            }
        }
    printf("%lld\n",res);
    return 0;
}
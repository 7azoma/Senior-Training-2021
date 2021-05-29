// https://vjudge.net/problem/POJ-3667
#include <iostream>
#include <cstdio>
#include <algorithm>
#define S second
#define F first

using namespace std;

const int N = 1<<17;

typedef long long ll;

int n;

struct node
{
    int pre, suf, mx;
    bool hasLazy, lazy;
    void set(bool isEmpty, int ns, int ne)
    {
        hasLazy = true;
        lazy = isEmpty;
        pre = suf = mx = (isEmpty ? ne - ns + 1 : 0);
    }
}tree[N<<1];

void pushDown(int ni, int ns, int ne)
{
    if(!tree[ni].hasLazy or ns == ne) return;
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    tree[lf].set(tree[ni].lazy, ns, mid);
    tree[rt].set(tree[ni].lazy, mid + 1, ne);
    tree[ni].hasLazy = false;
}

node merge(const node &lf, const node&rt, int ns, int ne)
{
    int mid = ns + (ne - ns) / 2;
    node ret;
    ret.pre = (lf.pre == mid - ns + 1 ? lf.pre + rt.pre : lf.pre);
    ret.suf = (rt.suf == ne - mid ? rt.suf + lf.suf : rt.suf);
    ret.mx = max(max(lf.mx, rt.mx), lf.suf + rt.pre);
    ret.hasLazy = false;
    return ret;
}

void update(int qs, int qe, bool isEmpty, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns > qe or ne < qs) return;
    if(ns >= qs and ne <= qe)
    {
        tree[ni].set(isEmpty, ns, ne);
        return;
    }
    pushDown(ni, ns, ne);
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(qs, qe, isEmpty, lf, ns, mid);
    update(qs, qe, isEmpty, rt, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[rt], ns, ne);
}

int query(int qs, int ni = 0, int ns = 0, int ne = n - 1)
{
    node &cur = tree[ni];
    if(cur.mx < qs) return -1;
    if(qs <= cur.pre) return ns;
    pushDown(ni, ns, ne);
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    node &LF = tree[lf];
    node &RT = tree[rt];
    if(qs <= LF.mx) return query(qs, lf, ns, mid);
    if(qs <= LF.suf + RT.pre) return mid - LF.suf + 1;
    return query(qs, rt, mid + 1, ne);
}

int main()
{
//    freopen("input.in", "rt", stdin);
    int q, qs, qsz, typ;
    scanf("%d%d", &n, &q);
    tree[0].set(1, 0, n - 1);
    while(q--)
    {
        scanf("%d%d", &typ, &qs);
        if(typ == 1)
        {
            int xx = query(qs);
            printf("%d\n", xx + 1);
            if(~xx) update(xx, xx + qs - 1, 0);
        }
        else
        {
            scanf("%d", &qsz);
            --qs;
            update(qs, qs + qsz - 1, 1);
        }
    }
    return 0;
}

// https://www.spoj.com/problems/GSS1/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

const int N = 1<<16;

typedef long long ll;

int n, arr[N];

struct node
{
    int pre, suf, sum, mx;
}tree[N<<1];

node merge(const node &lf, const node &rt)
{
    node ret;
    ret.sum = lf.sum + rt.sum;
    ret.pre = max(lf.pre, lf.sum + rt.pre);
    ret.suf = max(rt.suf, rt.sum + lf.suf);
    ret.mx = max({lf.mx, rt.mx, lf.suf + rt.pre});
    return ret;
}

void init(int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns == ne)
    {
//        tree[ni].pre = tree[ni].suf = tree[ni].mx = max(tree[ni].sum = arr[ns], 0); allows empty sub-array
        tree[ni].pre = tree[ni].suf = tree[ni].mx = tree[ni].sum = arr[ns];
        return;
    }
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    init(lf, ns, mid);
    init(rt, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[rt]);
}

node query(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ne < qs or ns > qe) return {-(int)1e9, -(int)1e9, 0, -(int)1e9};
    if(ns >= qs and ne <= qe) return tree[ni];
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return merge(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
}

int main()
{
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) scanf("%d", arr + i);
    init();
    int q, x, y;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d%d", &x, &y);
        printf("%d\n", query(--x, --y).mx);
    }
    return 0;
}
// https://www.spoj.com/problems/HORRIBLE/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

const int N = 1<<17;

typedef long long ll;

int n, arr[N];

struct node
{
    ll sum, lazy;
    void add(ll val, int ns, int ne)
    {
        sum += val * (ne - ns + 1);
        lazy += val;
    }
}tree[N<<1];

void init(int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns == ne)
    {
        tree[ni].sum = tree[ni].lazy = 0;
        return;
    }
    tree[ni].sum = tree[ni].lazy = 0;
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    init(lf, ns, mid);
    init(rt, mid + 1, ne);
}

void pushDown(int ni, int ns, int ne)
{
    if(!tree[ni].lazy or ns == ne) return;
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    tree[lf].add(tree[ni].lazy, ns, mid);
    tree[rt].add(tree[ni].lazy, mid + 1, ne);
    tree[ni].lazy = 0;
}

ll query(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ne < qs or ns > qe) return 0;
    if(ns >= qs and ne <= qe) return tree[ni].sum;
    pushDown(ni, ns, ne);
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return query(qs, qe, lf, ns, mid) + query(qs, qe, rt, mid + 1, ne);
}

void update(int qs, int qe, int val, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ne < qs or ns > qe) return;
    if(ns  >= qs and ne <= qe)
    {
        tree[ni].add(val, ns, ne);
        return;
    }
    pushDown(ni, ns, ne);
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    update(qs, qe, val, lf, ns, mid);
    update(qs, qe, val, rt, mid + 1, ne);
    tree[ni].sum = tree[lf].sum + tree[rt].sum;
}

int main()
{
    int t, q, typ, st, en, val;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &q);
        init();
        while(q--)
        {
            scanf("%d%d%d", &typ, &st, &en);
            --st, --en;
            if(!typ)
            {
                scanf("%d", &val);
                update(st, en, val);
            }
            else
            {
                printf("%lld\n", query(st, en));
            }
        }
    }
    return 0;
}
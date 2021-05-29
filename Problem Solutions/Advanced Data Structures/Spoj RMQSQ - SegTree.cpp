// https://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

const int N = 1<<17;

typedef long long ll;

int tree[N<<1], arr[N], n;

void init(int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns == ne)
    {
        tree[ni] = arr[ns];
        return;
    }
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    init(lf, ns, mid);
    init(rt, mid + 1, ne);
    tree[ni] = min(tree[lf], tree[rt]);
}

int query(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ne < qs or ns > qe) return INT_MAX;
    if(ns >= qs and ne <= qe) return tree[ni];
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return min(query(qs, qe, lf, ns, mid), query(qs, qe, rt, mid + 1, ne));
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
        printf("%d\n", query(x, y));
    }
    return 0;
}
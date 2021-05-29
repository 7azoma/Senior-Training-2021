// https://www.spoj.com/problems/MKTHNUM/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

const int N = 1<<17;

typedef long long ll;

int n, arr[N];
vector<int> tree[N<<1];

void init(int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns == ne)
    {
        tree[ni].emplace_back(arr[ns]);
        return;
    }
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    init(lf, ns, mid);
    init(rt, mid + 1, ne);
    merge(tree[lf].begin(), tree[lf].end(), tree[rt].begin(), tree[rt].end(), inserter(tree[ni], tree[ni].begin()));
}

int query(int qs, int qe, int val, int ni = 0, int ns = 0, int ne = n - 1)
{
    if(ns > qe or ne < qs) return 0;
    if(ns  >= qs and ne <= qe) return lower_bound(tree[ni].begin(), tree[ni].end(), val) - tree[ni].begin();
    int lf = ni * 2 + 1, rt = lf + 1, mid = ns + (ne - ns) / 2;
    return query(qs, qe, val, lf, ns, mid) + query(qs, qe, val, rt, mid + 1, ne);
}

int BS(int qs, int qe, int k)
{
    int st = -1e9, en = 1e9;
    while(st < en)
    {
        int mid = st + (en - st) / 2;
        if(query(qs, qe, mid) >= k) en = mid;
        else st = mid + 1;
    }
    return st;
}

int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < n ; i++)
    {
        scanf("%d", arr + i);
    }
    init();
    int qs, qe, k;
    while(m--)
    {
        scanf("%d%d%d", &qs, &qe, &k);
        printf("%d\n", BS(--qs, --qe, k) - 1);
    }
    return 0;
}
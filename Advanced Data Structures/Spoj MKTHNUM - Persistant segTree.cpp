// https://www.spoj.com/problems/MKTHNUM/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

const int N = 1<<17;

typedef long long ll;

int n;

extern struct node* empty;

struct node
{
    int sum;
    node *lf, *rt;
    node():lf(this), rt(this), sum(0){}
    node(int val, node* lf = empty, node*rt = empty):lf(lf), rt(rt), sum(val){}
};

node* empty = new node();
node* roots[N];

node* insert(int val, node* cur, int ns = -1e9, int  ne = 1e9)
{
    if(val < ns or val > ne) return cur;
    if(ns == ne) return new node(cur->sum + 1);
    int mid = ns + (ne - ns) / 2;
    node *LF = insert(val, cur->lf, ns, mid);
    node *RT = insert(val, cur->rt, mid + 1, ne);
    return new node(LF->sum + RT->sum, LF, RT);
//    return new node(cur->sum + 1, LF, RT);
}

int query(int k, node* en, node *stm1, int ns = -1e9, int  ne = 1e9)
{
    if(ns == ne) return ns;
    int lfsz = en->lf->sum - stm1->lf->sum;
    int mid = ns + (ne  - ns) / 2;
    if(k <= lfsz) return query(k,  en->lf, stm1->lf, ns, mid);
    return query(k - lfsz, en->rt, stm1->rt, mid + 1, ne);
}

int main()
{
    roots[0] = empty;
    int m, xx;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; i++)
    {
        scanf("%d", &xx);
        roots[i] = insert(xx, roots[i - 1]);
    }
    int qs, qe, k;
    while(m--)
    {
        scanf("%d%d%d", &qs, &qe, &k);
        printf("%d\n", query(k, roots[qe], roots[qs - 1]));
    }
    return 0;
}
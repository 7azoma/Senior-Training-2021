// https://www.spoj.com/problems/GSS4/en/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
struct node{
    bool lessThan2; ll sum;
};

const int N = (1 << 17);

ll n, a[N];
node tree[N << 1];

node merge(node &lf, node &ri){
    return { (lf.lessThan2 && ri.lessThan2) , lf.sum + ri.sum };
}

void init(int ni = 0, int ns = 0, int ne = n - 1){
    if (ns == ne){
        return void(tree[ni] = {a[ns] < 2, a[ns]});
    }
    int lf = 2 * ni + 1, ri = lf + 1, mid = ns + ((ne - ns) >> 1);
    init(lf, ns, mid);
    init(ri, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[ri]);
}

void update(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1){
    node &cur = tree[ni];
    if ( qs > ne or qe < ns or cur.lessThan2 ) return;
    if ( ns == ne ) {
        cur.sum = (ll)sqrtl(cur.sum);
        cur.lessThan2 = (cur.sum < 2);
        return;
    }
    int lf = 2 * ni + 1, ri = lf + 1, mid = ns + ((ne - ns) >> 1);
    update(qs, qe, lf, ns, mid);
    update(qs, qe, ri, mid + 1, ne);
    tree[ni] = merge(tree[lf], tree[ri]);
}

ll query(int qs, int qe, int ni = 0, int ns = 0, int ne = n - 1){
    if ( qs > ne or qe < ns ) return 0;
    if ( ns >= qs and ne <= qe ) return tree[ni].sum;
    int lf = 2 * ni + 1, ri = lf + 1, mid = ns + ((ne - ns) >> 1);
    return query(qs, qe, lf, ns, mid) + query(qs, qe, ri, mid + 1, ne);
}

int main(){
#ifdef CLion
    freopen("input.txt" , "r" , stdin);
#endif

    int cses = 1;
    while ( ~scanf("%lld" , &n) ){
        printf( "Case #%d:\n", cses);
        cses++;

        for ( int j = 0; j < n; ++j ){
            scanf( "%lld" , a + j);
        }
        init();

        int q; scanf("%d" , &q);
        for ( int _ = 1; _ <= q; ++_ ){
            int t, l, r;
            scanf("%d%d%d", &t, &l, &r);

            if ( r < l ){
                swap(l, r);
            }

            if (t == 0){
                update(--l, --r);
            }
            else{
                printf("%lld\n", query(--l, --r));
            }
        }
        puts("");
    }

    return 0;
}

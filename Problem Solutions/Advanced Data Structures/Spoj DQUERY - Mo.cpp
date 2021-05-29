// https://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e6 + 2;

int freq[N], a[N], qs[N], qe[N], qi[N], qAns[N], n, q, sq, s, e, ans;

void add(int val){
    ans += !freq[val]++;
}
void del(int val){
    ans -= !--freq[val];
}

void updateSE(int idx){
    while (e < qe[idx] + 1) add(a[e++]);
    while (s > qs[idx]) add(a[--s]);
    while (s < qs[idx]) del(a[s++]);
    while (e > qe[idx] + 1) del(a[--e]);
}

int main(){
#ifdef CLion
    freopen("input.txt" , "r" , stdin);
#endif

    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", a + i);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; ++i){
        scanf("%d%d", qs + i, qe + i);
        --qs[i]; --qe[i];
        qi[i] = i;
    }

    sq = sqrtl((n * 1LL * n) / q);
    sort(qi, qi + q, [](int a, int b){
        return make_pair(qs[a] / sq, qe[a]) < make_pair(qs[b] / sq, qe[b]);
    });

    for (int i = 0; i < q; ++i){
        updateSE(qi[i]);
        qAns[qi[i]] = ans;
    }

    for ( int i = 0; i < q; ++i ){
        printf("%d\n", qAns[i]);
    }
    return 0;
}
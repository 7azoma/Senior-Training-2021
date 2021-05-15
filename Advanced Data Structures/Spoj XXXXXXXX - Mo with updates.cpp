// https://w...content-available-to-author-only...j.com/problems/XXXXXXXX/en/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 5e4 + 5, Q = 1e5 + 5;
ll A[N], comp[N + Q], ans[Q], old[N + Q], nw[N + Q], updIdx[Q], sum;
int qs[Q], qe[Q], qi[Q], qt[Q], n, q, frq[N + Q];
int st, en, tim, B, compsz, nq;

void compress() {
    sort(comp, comp + compsz);
    compsz = unique(comp, comp + compsz) - comp;
    for (int i = 0; i < n; ++i)
        A[i] = lower_bound(comp, comp + compsz, A[i]) - comp;
    for (int i = 1; i <= tim; ++i) {
        old[i] = lower_bound(comp, comp + compsz, old[i]) - comp;
        nw[i] = lower_bound(comp, comp + compsz, nw[i]) - comp;
    }
}

void add(int cv) {
    if (!frq[cv]++)
        sum += comp[cv];
}

void remv(int cv) {
    if (!--frq[cv])
        sum -= comp[cv];
}

void update(int qId) {
    while (tim < qt[qId]) {
        tim++;
        if (updIdx[tim] >= st && updIdx[tim] < en) {
            remv(old[tim]);
            add(nw[tim]);
        }
        A[updIdx[tim]] = nw[tim];
    }
    while (tim > qt[qId]) {
        if (updIdx[tim] >= st && updIdx[tim] < en) {
            remv(nw[tim]);
            add(old[tim]);
        }
        A[updIdx[tim]] = old[tim];
        tim--;
    }
    while (en <= qe[qId])
        add(A[en++]);
    while (en - 1 > qe[qId])
        remv(A[--en]);
    while (st - 1 >= qs[qId])
        add(A[--st]);
    while (st < qs[qId])
        remv(A[st++]);
}

int main() {
    scanf("%d", &n);
    compsz = n;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", A + i);
        comp[i] = A[i];
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        char ch;
        int x, y;
        scanf(" %c%d%d", &ch, &x, &y);
        if (ch == 'Q') {
            qs[nq] = --x;
            qe[nq] = --y;
            qi[nq] = nq;
            qt[nq] = tim;
            nq++;
        } else {
            tim++;
            old[tim] = A[--x];
            nw[tim] = y;
            updIdx[tim] = x;
            A[x] = y;
            comp[compsz++] = y;
        }
    }
    compress();
    B = ceil(pow(n, 2.0 / 3.0));
    sort(qi, qi + nq, [](int a, int b) {
        int bsta = qs[a] / B, bena = qe[a] / B, bstb = qs[b] / B, benb = qe[b] / B;
        return tie(bsta, bena, qt[a]) < tie(bstb, benb, qt[b]);
    });
    for (int i = 0; i < nq; ++i) {
        update(qi[i]);
        ans[qi[i]]=sum;
    }
    for(int i = 0 ; i < nq;++i){
        printf("%lld\n",ans[i]);
    }
    return 0;
}
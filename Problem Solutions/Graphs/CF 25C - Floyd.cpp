#include<bits/stdc++.h>

using namespace std;


typedef long long ll;

const int N = 300 + 5;

int n;
int d[N][N];

void floyd() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}


int main() {
    scanf("%d ", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &d[i][j]);
        }
    }
    int k;
    scanf("%d", &k);
    for (int q = 0; q < k; ++q) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        --u;
        --v;
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min({d[i][j], d[i][u] + d[v][j] + c, d[i][v] + d[u][j] + c});
                if (i < j) {
                    sum += d[i][j];
                }
            }
        }
        printf("%lld\n", sum);
    }
}

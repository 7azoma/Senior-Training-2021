#include<bits/stdc++.h>
using namespace std;

#define var(x) ((x)<<1)
#define Not(x) ((x)^1)

const int N = 200 + 5;

bool adj[N][N];

void addOr(int x, int y) {
    adj[Not(x)][y] = adj[Not(y)][x] = 1;
}

void addImpl(int x, int y) {
    addOr(Not(x), y);
}

int n, m;
int cho[4];

void transClosure(){
    for (int k = 0; k < 2 * n; ++k) {
        for (int i = 0; i < 2*n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                adj[i][j] |= adj[i][k] && adj[k][j];
            }
        }
    }
}


int main() {
    int tt = 0;
    while(scanf("%d%d", &n, &m) && n) {
        memset(adj, 0, sizeof(adj));
        while (m--) {
            int k;
            scanf("%d", &k);
            for (int p = 0; p < k; ++p) {
                int bill;
                char vote;
                scanf("%d %c", &bill, &vote);
                bill--;
                cho[p] = var(bill);
                if (vote == 'n')
                    cho[p] = Not(cho[p]);
            }
            if (k <= 2) {
                for (int p = 0; p < k; ++p) {
                    addOr(cho[p], cho[p]);
                }
            }else{
                for (int p = 0; p < k; ++p) {
                    for (int r = 0; r < k; ++r) if(r != p){
                            addImpl(Not(cho[p]), cho[r]);
                        }
                }
            }
        }
        transClosure();
        printf("Case %d: ", tt+1);
        bool imp = false;
        string res;
        for (int i = 0; i < 2*n; i += 2) {
            if(adj[i][i+1] && adj[i+1][i]){
                puts("impossible");
                imp = true;
                break;
            }
            if(adj[i][i+1])
                res += 'n';
            else if(adj[i+1][i])
                res += 'y';
            else
                res += '?';
        }
        if(!imp)
            puts(res.c_str());
        ++tt;
    }
}

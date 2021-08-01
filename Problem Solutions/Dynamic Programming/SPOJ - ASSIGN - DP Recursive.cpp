#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n;
ll dp[1<<20];
int vis[1<<20],vid;
vector<vector<int>> subject;

ll solve(int mask){
    if(mask+1==(1<<n)) return 1;
    ll &ret=dp[mask];
    if(vis[mask]==vid) return ret;
    ret=0;
    vis[mask]=vid;
    int i=__builtin_popcount(mask);
    for(auto it:subject[i]){
        if(!((mask>>it)&1)){
            ret+=solve(mask|(1<<it));
        }
    }
    return ret;
}


int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        vid++;
        scanf("%d",&n);
        subject= vector<vector<int>>(n) ;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                scanf("%d",&x);
                if(x) subject[i].push_back(j);
            }
        }
        printf("%lld\n",solve(0));
    }
}

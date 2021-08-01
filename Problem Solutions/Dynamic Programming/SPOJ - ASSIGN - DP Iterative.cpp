#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n;
ll dp[1<<20];
vector<vector<int>> subject;



bool arr[20];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        subject= vector<vector<int>>(n) ;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                scanf("%d",&x);
                if(x) subject[i].push_back(j);
            }
        }
        dp[(1<<n)-1]=1;
        for (int i = n-1; ~i ; --i) {
            fill(arr,arr+n-i,0);
            fill(arr+n-i,arr+n,1);
            do{
                int mask=0;
                for (int j = 0; j < n; ++j) {
                    mask|=(arr[j]<<j);
                }
                ll &ret=dp[mask];
                ret=0;
                for(auto it:subject[i]){
                    if(!( (mask>>it)&1 ) ){
                        ret+=dp[mask|(1<<it)];
                    }
                }
            } while (next_permutation(arr,arr+n));
        }
        printf("%lld\n",dp[0]);
    }
}

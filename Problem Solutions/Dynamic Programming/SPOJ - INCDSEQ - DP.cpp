#include<bits/stdc++.h>
 typedef long long ll;
using namespace std;
const int N=1e4+10,MOD=5e6;
int arr[N],sorted[N],cnt;

int dp[51][N];

void add(int i,int j,int val){
    for(j++;j<=cnt;j+=(j&-j))
        dp[i][j-1]+=val,dp[i][j-1]%=MOD;
}

int get(int i,int j){
    int ret=0;
    for(j++;j;j-=(j&-j))
        ret+=dp[i][j-1],ret%=MOD;
    return ret;
}

int main(){
    int n,K;
    scanf("%d%d",&n,&K);
    for (int i = 1; i <= n; ++i) {
        scanf("%d",arr+i);
        sorted[i]=arr[i];
    }
    arr[0]=INT_MIN;
    sorted[0]=INT_MIN;
    //compression
    sort(sorted,sorted+n+1);
    cnt=unique(sorted,sorted+n+1)-sorted;
    for (int i = 0; i <= n; ++i) {
        arr[i]=lower_bound(sorted,sorted+cnt,arr[i])-sorted;
    }
    add(0,0,1);
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= K; ++k) {
            int val=arr[i];
            int g=get(k-1,val-1);
            int old=(get(k,val)-get(k,val-1)+MOD)%MOD;
            add(k,val,(g-old+MOD)%MOD);
        }
    }
    printf("%d\n",get(K,cnt-1));

}

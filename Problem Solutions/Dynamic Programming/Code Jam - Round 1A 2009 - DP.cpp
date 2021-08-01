/*
	Problem Link: https://codingcompetitions.withgoogle.com/codejam/round/0000000000432b26/0000000000432bd9
*/

#include<bits/stdc++.h>
 typedef long long ll;
using namespace std;

ll dp[41][41];
bool vis[41][41];

ll choose(int n,int r){
    if(n==r) return 1;
    if(!r) return 1;
    if(n<r) return 0;

    ll &ret=dp[n][r];
    if(vis[n][r]) return ret;
    vis[n][r]=1;

    return ret=choose(n-1,r-1)+choose(n-1,r);
}

double memo[41];
int visited[41],vid,c,n;

double solve(int collected){

    if(collected>=c) return 0;

    double &ret=memo[collected];
    if(visited[collected]==vid) return ret;
    visited[collected]=vid;

    double p=0,q=0;
    p=choose(collected,n)*1.0/choose(c,n);
    for(int i=1;i<=n;i++) {
        int j=n-i;
        q+=(choose(c-collected,i)*choose(collected,j)*1.0/choose(c,n))*(1+solve(collected+i));
    }
    return ret=(p+q)/(1-p);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        scanf("%d%d",&c,&n);
        vid++;
        printf("Case #%d: %.9lf\n",t,solve(0));
    }
}

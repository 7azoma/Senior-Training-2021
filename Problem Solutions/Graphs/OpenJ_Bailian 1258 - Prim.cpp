/*
	Agri-Net OpenJ_Bailian - 1258 
	Prim
 */
#include <cstdio>

#include <cstring>
#include <algorithm>

#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 1e3 + 5, M = 2 * N;
int adjMat[N][N], dis[N], notVis[N], notVisSz;
int n;
int prim(int src){
    memset(dis,0x3f,sizeof(dis[0])*n);
    dis[src]=0;
    for(int i=0;i<n;i++){
        notVis[i]=i;
    }
    notVisSz=n;
    int nxt=src, best=0;
    int res=0;
    while(nxt!=-1){
        res+=best;
        int u=notVis[nxt];
        notVis[nxt]=notVis[--notVisSz];
        nxt=-1;
        best=0x3f3f3f3f;
        for(int i=0;i<notVisSz;i++){
            int v=notVis[i];
            if(dis[v]> adjMat[u][v]){
                dis[v]=adjMat[u][v];
            }
            if(best > dis[v]){
                best=dis[v];
                nxt=i;
            }
        }
    }
    return res;
}
int main() {

//    freopen("agrinet.in","r",stdin);
//    freopen("agrinet.out","w",stdout);
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++)
           for(int j=0;j<n;j++)
               scanf("%d",adjMat[i]+j);

        printf("%d\n", prim(0));
    }
    return 0;
}

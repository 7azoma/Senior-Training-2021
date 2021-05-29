/**
 * https://vjudge.net/problem/POJ-2387
 * Til the Cows Come Home OpenJ_Bailian - 2387 
 * dijkstra N squared
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
void shortestPath(int src){
    memset(dis,0x3f,sizeof(dis[0])*n);
    dis[src]=0;
    for(int i=0;i<n;i++){
        notVis[i]=i;
    }
    notVisSz=n;
    int nxt=src, best;
    while(nxt!=-1){
        int u=notVis[nxt];
        notVis[nxt]=notVis[--notVisSz];
        nxt=-1;
        best=0x3f3f3f3f;
        for(int i=0;i<notVisSz;i++){
            int v=notVis[i];
            if(dis[v]> dis[u]+adjMat[u][v]){
                dis[v]=dis[u]+adjMat[u][v];
            }
            if(best > dis[v]){
                best=dis[v];
                nxt=i;
            }
        }
    }
}
int main() {
    memset(adjMat,0x3f,sizeof(adjMat));
    int m;
    scanf("%d%d",&m,&n);

    while(m--){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        u--,v--;
        adjMat[u][v]=adjMat[v][u]=min(adjMat[u][v],c);

    }
    shortestPath(n-1);
    printf("%d\n",dis[0]);
    return 0;
}

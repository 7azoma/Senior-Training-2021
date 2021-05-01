#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1e5 + 5, SQ = 317;

int arr[N], pre[SQ], n, sq;

int RMQ(int st, int en)
{
    int stB = st / sq, enB = en / sq;
    if(stB == enB) return *min_element(arr + st, arr + en + 1);
    int ret = min(*min_element(arr + st, arr + (stB + 1) * sq), *min_element(arr  + enB * sq, arr + en + 1));
    if(stB + 1 != enB) ret = min(ret, *min_element(pre + stB + 1, pre + enB));
    return ret;
}

int main()
{
    scanf("%d", &n);
    sq = ceil(sqrt(n));
    for(int i = 0, j = 0 ; i < n ; i += sq, j++)
    {
        pre[j] = INT_MAX;
        for(int k = 0 ; k < sq and k + i < n ; k++)
        {
            scanf("%d", arr + i + k);
            pre[j] = min(pre[j], arr[i + k]);
        }
    }
    int q, st, en;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d%d", &st, &en);
        printf("%d\n", RMQ(st, en));
    }
    return 0;
}
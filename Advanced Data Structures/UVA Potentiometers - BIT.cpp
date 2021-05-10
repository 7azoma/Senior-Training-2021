// https://vjudge.net/problem/UVA-12086
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

struct BIT
{
    int tree[N];
    void init()
    {
        memset(tree, 0, sizeof tree);
    }
    void add(int pos, int val)
    {
        for(++pos ; pos <= N ; pos += (pos & (-pos))) tree[pos - 1] += val;
    }
    int get(int pos)
    {
        int ret = 0;
        for(++pos ; pos ; pos -= (pos & (-pos))) ret += tree[pos - 1];
        return ret;
    }
}bit;

char str[4];
int arr[N];

int main()
{
    int t, n, q, x, y, tc = 0;
    char *sep = "";
    while(scanf("%d", &n), n)
    {
        printf("%sCase %d:\n", sep, ++tc);
        sep = "\n";
        bit.init();
        for(int i = 1 ; i <= n ; i++) scanf("%d", arr + i), bit.add(i, arr[i]);
        while(scanf("%s", str), str[0] != 'E')
        {
            scanf("%d%d", &x, &y);
            if(str[0] == 'S')
            {
                bit.add(x, y - arr[x]);
                arr[x] = y;
            }
            else
            {
                printf("%d\n", bit.get(y) - bit.get(x - 1));
            }
        }
    }
    return 0;
}

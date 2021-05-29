// https://www.spoj.com/problems/MATSUM/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1e3 + 30;

struct bit2D
{
    int tree[N][N];
    void init()
    {
        memset(tree, 0, sizeof tree);
    }
    ll get(int i, int j)
    {
        ll ret = 0;
        for(i++ ; i ; i -= (i & (-i)))
        {
            for(int jj = j + 1 ; jj ; jj -= (jj & (-jj)))
            {
                ret += tree[i - 1][jj - 1];
            }
        }
        return ret;
    }
    void add(int i, int j, ll val)
    {
        for(i++ ; i <= N ; i += (i & (-i)))
        {
            for(int jj = j + 1 ; jj <= N ; jj += (jj & (-jj)))
            {
                tree[i - 1][jj - 1] += val;
            }
        }
    }
    ll get(int si, int sj, int ei, int ej)
    {
        return get(ei, ej) - get(ei, sj - 1) - get(si - 1, ej) + get(si - 1, sj - 1);
    }
}bit;

char str[4];
int arr[N][N];

int main()
{
    int t, n, x, y, val, si, sj, ei, ej;
    scanf("%d", &t);
    while(t--)
    {
        bit.init();
        memset(arr, 0, sizeof arr);
        scanf("%d", &n);
        while(scanf("%s", str), str[0] != 'E')
        {
            if(str[1] == 'E')
            {
                // set
                scanf("%d%d%d", &x, &y, &val);
                bit.add(x, y, val - arr[x][y]);
                arr[x][y] = val;
            }
            else
            {
                // sum
                scanf("%d%d%d%d", &si, &sj, &ei, &ej);
                printf("%lld\n", bit.get(si, sj, ei, ej));
            }
        }
        puts("");
    }
    return 0;
}

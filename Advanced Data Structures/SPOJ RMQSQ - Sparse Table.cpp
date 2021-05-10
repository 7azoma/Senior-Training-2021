// https://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1e5 + 5, LG = 17;

int sp[LG][N], lg[N], arr[N], n;

void pre()
{
    lg[0] = -1;
    for(int i = 0 ; i < N - 1 ; i++)
    {
        sp[0][i] = i;
        lg[i + 1] = lg[i] + !(i & (i + 1));
    }
}

void buildSP()
{
    static int dummy = (pre(), 0);
    for(int j = 1 ; (1 << j) <= n ; j++)
    {
        for(int i = 0 ; i + (1 << j) <= n ; i++)
        {
            int a = sp[j - 1][i];
            int b = sp[j - 1][i + (1<<(j - 1))];
            sp[j][i] = arr[a] < arr[b] ? a : b;
        }
    }
}

int getMnInd(int st, int en)
{
    int sz = en - st + 1;
    int l = lg[sz];
    int a = sp[l][st];
    int b = sp[l][en - (1<<l) + 1];
    return arr[a] < arr[b] ? a : b;
}

int main()
{
    int q, l, r;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) scanf("%d", arr + i);
    buildSP();
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", arr[getMnInd(l, r)]);
    }
    return 0;
}

https://www.spoj.com/problems/HORRIBLE/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1 << 17;

struct bitRange
{
    ll m[N], c[N];
    void init(int n)
    {
        memset(m, 0, n * sizeof(m[0]));
        memset(c, 0, n * sizeof(m[0]));
    }
    void add(int pos, ll mVal, ll cVal)
    {
        for(++pos ; pos <= N ; pos += (pos & (-pos)))
        {
            m[pos - 1] += mVal;
            c[pos - 1] += cVal;
        }
    }
    ll get(int pos)
    {
        ll ret = 0;
        int x = pos;
        for(pos++ ; pos ; pos -= (pos & (-pos)))
        {
            ret += m[pos - 1] * x + c[pos - 1];
        }
        return ret;
    }
    void addRange(int st, int en, ll val)
    {
        add(st, val, -val * (st - 1));
        add(en + 1, -val, val * en);
    }
}bit;

int main()
{
    int t, n, q, typ, st, en, val;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &q);
        bit.init(n + 1);
        while(q--)
        {
            scanf("%d%d%d", &typ, &st, &en);
            if(!typ)
            {
                scanf("%d", &val);
                bit.addRange(st, en, val);
            }
            else
            {
                printf("%lld\n", bit.get(en) - bit.get(st - 1));
            }
        }
    }
    return 0;
}

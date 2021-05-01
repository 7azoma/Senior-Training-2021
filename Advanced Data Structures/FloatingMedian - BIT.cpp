#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1 << 18;

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
    int find(int t)
    {
        int st = 0;
        for(int sz = N >> 1 ; sz ; sz >>= 1)
        {
            if(tree[st + sz - 1] < t)
            {
                t -= tree[(st += sz) - 1];
            }
        }
        return st;
    }
};

struct multiSet
{
    BIT bit;
    multiSet()
    {
        bit.init();
        bit.add(0, -1);
    }
    void insert(int val)
    {
        bit.add(val, 1);
    }
    void erase(int val)
    {
        bit.add(val, -1);
    }
    int count(int val)
    {
        return bit.get(val) - bit.get(val - 1);
    }
    int size()
    {
        return bit.get(N - 1) + 1;
    }
    int at(int ind)
    {
        return bit.find(ind);
    }
}mySet;

class FloatingMedian
{
public:
    long long sumOfMedians(int cur, int mul, int add, int N, int K)
    {
        int i;
        deque<int> dq;
        for(i = 0 ; i < K ; i++)
        {
            dq.emplace_back(cur);
            mySet.insert(cur);
            cur = (1LL * cur * mul + add) % 65536;
        }
        ll res = 0;
        for( ; i <= N ; i++)
        {
            res += mySet.at((K + 1) / 2 - 1);
            mySet.erase(dq.front());
            dq.pop_front();
            dq.emplace_back(cur);
            mySet.insert(cur);
            cur = (1LL * cur * mul + add) % 65536;
        }
        return res;
    }
};

int main()
{
    FloatingMedian temp;
    printf("%lld\n", temp.sumOfMedians(4123, 2341, 1231, 7, 3));
    return 0;
}
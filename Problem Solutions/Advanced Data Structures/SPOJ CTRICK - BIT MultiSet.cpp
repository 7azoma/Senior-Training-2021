// https://www.spoj.com/problems/CTRICK/
#include <bits/stdc++.h>
#define S second
#define F first

using namespace std;

typedef long long ll;

const int N = 1 << 16;

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

int arr[N], res[N];

int main()
{
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int m = n, frnt = 0;
//        iota(arr, arr + n, 0);
        for(int i = 0 ; i < n ; i++) mySet.insert(i);
        for(int i = 1 ; i <= n ; i++)
        {
//            rotate(arr, arr + i % m, arr + m);
            frnt = (frnt + i) % m;
            m--;
            int x = mySet.at(frnt);
            res[x] = i;
//            rotate(arr + frnt, arr + frnt + 1, arr + m--);
            mySet.erase(x);
        }
        for(int i = 0 ; i < n ; i++) printf("%d%c", res[i], " \n"[i == n - 1]);
    }
    return 0;
}

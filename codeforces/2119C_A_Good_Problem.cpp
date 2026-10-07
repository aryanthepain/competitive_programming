// author: Aryanthepain
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;
#define all(v) v.begin(), v.end()
#define srt(v) sort(v.begin(), v.end())
#define minm(v) *min_element(v.begin(), v.end())
#define maxm(v) *max_element(v.begin(), v.end())
#define add(v) accumulate(v.begin(), v.end(), 0)

#define You_are_the_best         \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

ll lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        // lessgo();
        cout << lessgo() << endl;
    }

    return 0;
}

ll lessgo()
{
    ll n, l, r, k;
    cin >> n >> l >> r >> k;

    if (r < l)
    {
        return -1;
    }

    if (n & 1)
    {
        return l;
    }

    if (n < 4)
    {
        return -1;
    }

    ll mask;
    for (ll i = 0; i < 61; i++)
    {
        mask = (1LL << i);
        if (mask > l)
        {
            break;
        }
    }

    if (mask > r)
    {
        return -1;
    }

    if ((k == n) || (k == (n - 1)))
    {
        return mask;
    }

    return l;

    return 0;
}
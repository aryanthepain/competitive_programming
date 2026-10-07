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
    ll a, b, x, y;
    cin >> a >> b >> x >> y;

    if (a == b)
    {
        return 0;
    }
    if (a > b)
    {
        if (a == b + 1 && (a & 1))
        {
            return y;
        }
        return -1;
    }

    ll d = b - a;
    int parity = a & 1;
    ll n0 = (parity == 0 ? (d + 1) / 2 : d / 2);
    ll n1 = d - n0;
    ll cost = n0 * min(x, y) + n1 * x;
    return cost;

    return 0;
}
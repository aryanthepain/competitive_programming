// author: Aryanthepain
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define You_are_the_best         \
    ios::sync_with_stdio(false); \
    cin.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

void lessgo();
int main()
{
    You_are_the_best;
    size_t t;
    // cin >> t;
    t = 1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    vector<vector<ll>> v(9, vector<ll>(9));

    for (ll i = 0; i < 9; i++)
    {
        for (ll j = 0; j < 9; j++)
        {
            v[i][j] = (i + 1) * (j + 1);
        }
    }
    // debug(v);

    ll x;
    cin >> x;
    // debug(x);
    ll sum = 0;
    for (ll i = 0; i < 9; i++)
    {
        for (ll j = 0; j < 9; j++)
        {
            if (v[i][j] != x)
            {
                sum += v[i][j];
            }
        }
    }

    cout << sum << endl;

    return;
}
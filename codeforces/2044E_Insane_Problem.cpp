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
    cin >> t;
    // t=1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    double k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    ll count = 0;
    double kn = 1;
    for (ll n = 0; l1 * kn <= r2; kn *= k)
    {
        ll upper_limit = min(r1, floor(r2 / kn));
        ll lower_limit = max(l1, ceil(l2 / kn));
        count += max<ll>(0, 1 + upper_limit - lower_limit);
    }

    cout << count << endl;

    return;
}
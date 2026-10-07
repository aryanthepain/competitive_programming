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
    // cin >> t;

    while (t--)
    {
        // lessgo();
        cout << lessgo() << endl;
    }

    return 0;
}

ll lessgo()
{
    ll n;

    cin >> n;

    vll a(3);
    cin >> a[0] >> a[1] >> a[2];

    vll v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    srt(v);
    srt(a);

    debug(v);
    debug(a);

    ll itr1 = 0, itr2 = n - 1;

    ll ans = 0;

    for (int i = 2; i >= 0; i--)
    {
        if (!a[i])
        {
            continue;
        }

        if (a[i] < 0)
        {
            ans += v[itr1] * a[i];
            itr1++;
        }
        else
        {
            ans += v[itr2] * a[i];
            itr2--;
        }
    }

    return ans;
}
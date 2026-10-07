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
        lessgo();
        // cout<<lessgo()<<endl;
    }

    return 0;
}

ll lessgo()
{
    int n, c;
    cin >> n >> c;
    vll a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i]; // input the array

    srt(a); // sort the array
    ll ans = 0;

    auto x = upper_bound(all(a), c) - a.begin();
    ans += n - x;

    ll multiplier = 0;
    for (int i = x - 1; i >= 0; i--)
    {
        if (a[i] * 1 << multiplier <= c)
        {
            multiplier++;
        }
        else
        {
            ans++;
        }
    }

    cout << ans << endl; // output the result

    return 0;
}
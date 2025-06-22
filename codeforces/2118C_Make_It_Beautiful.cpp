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
    cin.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

ll lessgo();

void hi()
{
    cout << lessgo() << endl;

    return;
}

int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        hi();
    }

    return 0;
}

ll lessgo()
{
    ll n, k;
    cin >> n >> k;
    ll ans = 0;

    // input vector
    vll a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        ans += __builtin_popcountll(a[i]); // add base set bits
    }

    for (ll i = 0; i < 61; i++)
    {
        ll multiplier = (1ll << i); // 2^i or 1 in ith position and rest 0s

        for (auto x : a)
        {
            if (!(x & multiplier) && (k >= multiplier)) // if 0 in jth position in the number and cost is still left
            {
                k -= multiplier; // subtract the cost from k
                ans++;
            }
            else if (k < multiplier)
            {
                return ans;
            }
        }
    }

    return ans;
}
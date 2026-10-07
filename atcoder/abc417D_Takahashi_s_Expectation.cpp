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

ll f(ll i, ll mood, vector<vll> &a, vector<vll> &dp)
{
    // base case
    if (i < 0)
        return 0;

    // dp line
    if (dp[i][mood] != -1)
        return dp[i][mood];

    // all stuff
    ll ans = 0;
    if (mood >= a[i][0])
    {
        ans = mood + a[i][1] + f(i + 1, mood + a[i][1], a, dp);
    }
    else
    {
        ans = max(0LL, mood - a[i][2]) + f(i + 1, max(0LL, mood - a[i][2]), a, dp);
    }

    return dp[i][mood] = ans;
}

ll lessgo(vector<vll> &a);
int main()
{
    You_are_the_best;
    ll n;
    cin >> n;
    vector<vll> a(n, vll(3));
    for (int i = 0; i < n; i++)
    {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    size_t m = 1;
    cin >> m;
    vector<vll> dp(n, vll(m, -1));

    while (m--)
    {
        // lessgo();
        ll mood;
        cin >> mood;
        cout << f(n - 1, mood, a, dp) << endl;
    }

    return 0;
}

ll lessgo(vector<vll> &a)
{
    ll mood;
    cin >> mood;

    for (auto &gift : a)
    {
        if (gift[0] >= mood)
        {
            mood += gift[1];
        }
        else
        {
            mood = max(0LL, mood - gift[2]);
        }
    }

    return mood;
}
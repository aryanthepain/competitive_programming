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

vector<int> pref(2e5 + 5, 0);
ll lessgo()
{
    ll n;
    cin >> n;
    ll ans = n * (n + 1) * (n + 2) / 6;
    pref[0] = 0;

    string s;
    cin >> s;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1') // 1 occurs
        {
            pref[i + 1] = pref[i] + 1;
        }
        else // 0 occurs
        {
            pref[i + 1] = pref[i] - 1;
        }
    }

    sort(pref.begin(), pref.begin() + n + 1);
    // debug(pref);

    for (ll i = 0; i < n + 1; i++)
    {
        ans += (ll)pref[i] * ((2 * i) - n);
    }

    return ans / 2;
}
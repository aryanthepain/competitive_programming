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

int main()
{
    You_are_the_best;

    // input
    ll n;
    cin >> n;
    vll a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; i + j < n; j++)
        {
            if (j == (a[i] + a[i + j]))
            {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
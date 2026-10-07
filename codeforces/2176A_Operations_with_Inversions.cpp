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

    debug(t);

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
    ll count = 0;
    vll a(n, 0);
    for (auto &i : a)
        cin >> i;

    debug(n);
    debug(a);

    for (ll j = n - 1; j > 0; j--)
    {
        for (ll i = j - 1; i >= 0; i--)
        {
            if (a[i] > a[j])
            {
                count++;
                break;
            }
        }
    }

    return count;

    return 0;
}
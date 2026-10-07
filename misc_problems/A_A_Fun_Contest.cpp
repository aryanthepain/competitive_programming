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
    ll n, k;
    cin >> n >> k;

    ll i;
    for (i = 1; i < n; i++)
    {
        if (k <= i)
        {
            break;
        }

        k -= i;
    }
    ll first_b = n - i;
    ll second_b = n - k + 1;

    for (ll i = 1; i < n + 1; i++)
    {
        if (i == first_b || i == second_b)
        {
            cout << 'b';
            continue;
        }

        cout << 'a';
    }

    cout << endl;
    return 0;
}
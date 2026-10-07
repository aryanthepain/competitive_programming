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

vector<string> v;

ll lessgo(ll i);
int main()
{
    You_are_the_best;
    ll t;
    cin >> t;
    v.reserve((t + 2));
    ll sum = 1;
    for (ll i = 2; i < t + 2; i++)
    {
        sum += i;
        v[i].reserve(sum);
    }

    v = vector<string>(t + 2);
    v[0] = "0";
    v[1] = "1";

    for (ll i = 2; i < t + 2; i++)
    {
        lessgo(i);
    }

    return 0;
}

ll lessgo(ll i)
{
    ll l, r, x;
    cin >> l >> r >> x;
    v[i] = v[l] + v[r];
    cout << v[i][x - 1] << endl;

    return 0;
}
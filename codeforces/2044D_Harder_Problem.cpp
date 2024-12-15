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
    ll n;
    cin >> n;

    vector<ll> input_vect;
    unordered_set<ll> s;

    for (size_t i = 0; i < n; i++)
    {
        ll a;
        cin >> a;
        if (s.find(a) == s.end())
        {
            s.insert(a);
            input_vect.push_back(a);
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        if (s.find(i) == s.end())
        {
            input_vect.push_back(i);
        }
    }
    // debug(input_vect);
    // debug(input_vect.size());

    // Print elements
    for (ll i = 0; i < n; i++)
    {
        cout << input_vect[i] << " ";
    }

    cout << endl;

    return;
}
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
    // cin >> t;
    t = 1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    ll a;
    cin >> a;
    ll b;
    cin >> b;

    cout << (a + b) * (a + b) << endl;

    return;
}
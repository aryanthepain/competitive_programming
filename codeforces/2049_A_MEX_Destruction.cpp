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

template <typename T>
ll input_vector(vector<T> &v, ll n)
{
    ll zero_count = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> v[i];
        if (v[i] == 0)
            zero_count++;
    }

    return zero_count;
}

void lessgo()
{
    ll n;
    cin >> n;

    vector<ll> v(n);
    ll zero_count = input_vector(v, n);

    if (zero_count == 0)
    {
        cout << "1" << endl;
        return;
    }
    if (zero_count == n)
    {
        cout << "0" << endl;
        return;
    }

    ll l = 0;
    ll r = n - 1;

    while (v[l] == 0 || v[r] == 0)
    {
        if (v[l] == 0)
        {
            l++;
            zero_count--;
        }
        if (v[r] == 0)
        {
            r--;
            zero_count--;
        }

        if (zero_count == 0)
        {
            cout << "1" << endl;
            return;
        }
    }

    cout << "2" << endl;

    return;
}
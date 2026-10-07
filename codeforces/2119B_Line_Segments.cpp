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
const int MAX = 1e4 + 4;
vector<ll> arr(MAX);

ll lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        // lessgo();
        // cout<<lessgo()<<endl;

        if (lessgo())
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}

ll lessgo()
{
    ll n;
    cin >> n;
    ll px, py, qx, qy;
    cin >> px >> py >> qx >> qy;

    ll sum = 0;
    ll max_num = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
        max_num = max(max_num, arr[i]);
    }

    double dist = (double)sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));

    if (sum < dist)
    {
        return false;
    }
    if (sum == dist)
    {
        return true;
    }

    if (2 * max_num - sum > dist)
    {
        return false;
    }

    return true;
}
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
    int n;
    cin >> n;

    int num_zeros = 0;
    int num_ones = 0;
    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
            num_zeros++;
        else if (x == 1)
            num_ones++;
        else
        {
            ans += x;
        }
    }

    // add number of 2s
    if (num_zeros < num_ones)
    {
        swap(num_zeros, num_ones);
    }

    ans += 2 * num_ones;
    num_zeros -= num_ones;
    ans += num_zeros;

    cout << ans << endl;
    return 0;
}
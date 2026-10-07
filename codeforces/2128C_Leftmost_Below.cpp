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
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i]; // input the array

    int minx = v[0];
    for (int i = 1; i < n; i++)
    {
        // lesser
        if (v[i] <= minx)
        {
            minx = v[i];
            continue;
        }

        // greater
        if (((v[i] + 1) / 2 - 1) < minx && v[i] - ((v[i] + 1) / 2 - 1) <= minx)
        {
            continue;
        }

        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    return 0;
}
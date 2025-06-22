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

void lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    int n;
    cin >> n;

    cout << 2 * n - 2 << endl;
    // first row 2 to n reverse
    cout << 1 << " " << 2 << " " << n << endl;

    // mid rows 1 to I and i+1 to n reverse
    for (int i = 2; i < n; i++)
    {
        cout << i << " " << 1 << " " << i << endl;
        cout << i << " " << i + 1 << " " << n << endl;
    }
    if (n < 2)
        return;
    // last row 1 to n reverse
    cout << n << " " << 1 << " " << n << endl;

    return;
}
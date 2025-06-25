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
    // taking input

    int n;
    cin >> n;
    int s;
    cin >> s;
    int minnum = s;
    int maxnum = s;

    int a;
    cin >> a;

    minnum = min(a, minnum);

    for (int i = 0; i < n - 1; i++)
    {
        cin >> a;
    }
    maxnum = max(maxnum, a);

    int sum = maxnum - minnum + min(abs(maxnum - s), abs(s - minnum));

    cout << sum << endl;

    return;
}
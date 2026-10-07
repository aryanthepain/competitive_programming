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
        // lessgo();
        cout << lessgo() << endl;
    }

    return 0;
}

bool isOne(char c)
{
    return c == '1';
}

ll lessgo()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;

    ll count = 0;

    // find first occurrence of 1
    ll firstOne = s.find('1');
    ll onePtr = firstOne;

    for (ll i = firstOne + 1; i < n; i++)
    {
        if (s[i] == '1')
        {
            onePtr = i;
            continue;
        }

        // s[i] is 0
        ll shifts = (i - onePtr);
        count = max(count, shifts);
    }

    if (firstOne != 0)
    {
        ll shifts = firstOne + n - onePtr - 1;
        count = max(count, shifts);
    }

    return count;

    return 0;
}
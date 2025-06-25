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
    string s;
    cin >> s;

    map<char, int> m;

    if (s[0] == s[n - 1])
    {
        m[s[0]] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        if (m[s[i]])
        {
            m[s[i]]++;
        }
        else
        {
            m[s[i]] = 1;
        }

        if (m[s[i]] == 2)
        {
            cout << "Yes" << endl;
            return;
        }
    }

    cout << "No" << endl;

    return;
}
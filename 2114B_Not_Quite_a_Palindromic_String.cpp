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
    int n;
    cin >> n;
    int k;
    cin >> k;
    string s;
    cin >> s;

    int zero_count = 0;
    int one_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            zero_count++;
        }
        else
        {
            one_count++;
        }
    }

    // one count is always larger value
    if (zero_count > one_count)
    {
        swap(zero_count, one_count);
    }
    int max_count = one_count / 2 + zero_count / 2;
    int min_count = (one_count - zero_count) / 2;

    if (k < min_count || k > max_count)
    {
        cout << "NO" << endl;
        return;
    }

    if ((k - min_count) % 2 == 0)
    {
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;

    return;
}
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

int lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        cout << lessgo() << endl;
    }

    return 0;
}

int lessgo()
{
    string l, r;
    cin >> l >> r;
    int n = l.size();
    if (l == r)
    {
        return n * 2;
    }

    // part 1- prefix
    int i = 0;
    while (i < n && l[i] == r[i])
    {
        i++;
    }

    // first after common
    if (l[i] + 1 < r[i])
    {
        return i * 2;
    }
    // choosing one of the two numbers
    int ans = 2 * i + 1;

    // find number of 9s in l and numbers of 0s in r
    for (int j = i + 1; j < n; j++)
    {
        if (l[j] == '9' && r[j] == '0')
        {
            ans++;
        }
        else
        {
            break;
        }
    }

    return ans;
}
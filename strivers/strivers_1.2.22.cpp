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

void printSpace(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }

    return;
}

void printStar(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "*";
    }

    return;
}

int main()
{
    You_are_the_best;

    int n = 4;
    // cin >> n;

    for (int i = 1; i <= n * 2 - 1; i++)
    {
        for (int j = 1; j <= n * 2 - 1; j++)
        {
            int offset = max(abs(i - n), abs(j - n));
            cout << offset + 1;
        }
        cout << endl;
    }

    return 0;
}
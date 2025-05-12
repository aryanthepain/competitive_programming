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

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        printSpace(n - i);
        printStar(2 * i - 1);
        cout << endl;
    }

    return 0;
}
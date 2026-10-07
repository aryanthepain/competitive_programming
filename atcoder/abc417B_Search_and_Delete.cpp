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

int main()
{
    You_are_the_best;

    // take input
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> b(m);
    for (int i = 0; i < m; i++)
        cin >> b[i];

    srt(b);

    vector<int> ans;
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        // push
        if (a[i] < b[j])
        {
            ans.push_back(a[i]);
            i++;
        }
        else if (a[i] == b[j])
        {
            i++;
            j++;
        }
        else
        {
            // if a[i] > b[j]
            j++;
        }
    }

    // print the remaining elements of a
    while (i < n)
    {
        ans.push_back(a[i]);
        i++;
    }

    // print the result
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
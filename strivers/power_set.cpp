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
    // cin >> t;

    while (t--)
    {
        lessgo();
        // cout<<lessgo()<<endl;
    }

    return 0;
}

ll lessgo()
{
    // no of integers
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    int subsets = 1 << n;

    vector<vector<int>> ans;
    for (int i = 0; i < subsets; i++)
    {
        vector<int> list;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                list.push_back(nums[j]);
            }
        }
        ans.push_back(list);
    }
    debug(ans);  

    return 0;
}
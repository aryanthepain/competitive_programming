#include <bits/stdc++.h>
using namespace std;

int f(int i1, int i2, string &s1, string &s2, vector<vector<int>> &dp)
{
    // base case
    if (i1 < 0 || i2 < 0)
    {
        return 0;
    }

    // dp line
    if (dp[i1][i2] != -1)
        return dp[i1][i2];
    // all stuffs
    if (s1[i1] == s2[i2])
        return dp[i1][i2] = 1 + f(i1 - 1, i2 - 1, s1, s2, dp);
    // else
    return dp[i1][i2] = max(f(i1 - 1, i2, s1, s2, dp), f(i1, i2 - 1, s1, s2, dp));
}
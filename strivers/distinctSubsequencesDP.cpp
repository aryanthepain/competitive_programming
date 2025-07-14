#include <bits/stdc++.h>
using namespace std;

int f(int m, int n, string &s, string &t, vector<vector<int>> &dp){
    // base case
    if(m<0 || n<0){
        return 0;
    }
    if(n==0)
        return dp[m][n] = ((s[m]==t[n])?1:0) + f(m-1, n, s, t, dp);

    // dp line
    if(dp[m][n]!=-1) return dp[m][n];

    if(s[m]==t[n])
        return dp[m][n] = f(m-1, n-1, s, t, dp) + f(m-1, n, s, t, dp);
    else
        return dp[m][n] = f(m-1, n, s, t, dp);
}
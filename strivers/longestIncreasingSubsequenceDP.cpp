#include <bits/stdc++.h>
using namespace std;

int f(int ind, int last, vector<int> &nums, vector<vector<int>> &dp){
    // base case
    if(ind<0) return 0;
    
    // dp line
    if(dp[ind][last]!=-1) return dp[ind][last];

    // do all stuffs
    if(nums[ind]<last)
        return dp[ind][last] = max(1 + f(ind-1, nums[ind], nums, dp), f(ind-1, last, nums, dp));
    else 
        return dp[ind][last] = (f(ind-1, last, nums, dp));
}
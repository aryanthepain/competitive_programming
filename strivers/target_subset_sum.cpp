#include <bits/stdc++.h>
using namespace std;

bool f(int index, int sum, vector<vector<short>> &dp, vector<int> &nums){
    // base case
    if(sum<0) return false;
    if(sum==0) return true;
    if(index==0){ 
        if(sum==nums[index]) return true;
        else return false;
    }
    
    
    // dp line
    if(dp[index][sum]!=-1) return dp[index][sum];

    // all stuffs
    return dp[index][sum] = f(index - 1, sum - nums[index], dp, nums) || f(index - 1, sum, dp, nums);
}

int main(){
    vector<int> nums;
    int target;
    int x; cin >> x;

    if(x==0){
        nums = {1,2,7,3};
        target = 6;
    } else {
        nums = {2,3,5};
        target=6;
    }


    int n = nums.size();
    vector<vector<short>> dp(n, vector<short>(target+1, -1));
    
    cout << (f(n-1, target, dp, nums)? "true" : "false") << endl;
    
    // better solution is to find a subsequence with target sum as sum_of_all/2

    // tabulation
    // int n = nums.size();
    // vector<vector<bool>> dp(n, vector<bool>(2*(INF)+1, false));

    // // base case
    // dp[0][INF+nums[i]] = dp[0][INF-nums[i]] = true;

    // for(int i=1; i<n; i++){
    //     for(int j=0; j<dp[0].size(); j++){
    //         dp[i][j] = dp[i-1][INF+]
    //     }
    // }



    return 0;
}
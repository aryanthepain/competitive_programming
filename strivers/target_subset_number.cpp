#include <bits/stdc++.h>
using namespace std;

int f(int index, int sum, vector<vector<int>> &dp, vector<int> &nums){
    // base case
    if(sum<0) return 0;
    if(sum==0) return 1;
    if(index==0){ 
        if(sum==nums[index]) return 1;
        else return 0;
    }
    
    
    // dp line
    if(dp[index][sum]!=-1) return dp[index][sum];

    // all stuffs
    return dp[index][sum] = f(index - 1, sum - nums[index], dp, nums) + f(index - 1, sum, dp, nums);
}

int main(){
    vector<int> nums;
    int target;
    int x; cin >> x;

    if(x==0){
        nums = {2, 3, 5, 16, 8, 10};
        target = 10;
    } else {
        nums = {1, 2, 3, 4, 5};
        target=5;
    }


    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(target+1, -1));
    
    cout << f(n-1, target, dp, nums) << endl;

    return 0;
}
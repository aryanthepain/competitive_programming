#include <bits/stdc++.h>
using namespace std;

int f(int curr, vector<int> &dp, vector<int> &val){
    if(curr<0) return 0; // base case
    if(dp[curr]!=-1) return dp[curr]; // dp line

    return dp[curr] = max(val[curr] + f(curr-2, dp, val), f(curr-1, dp, val)); // all stuffs on index
}
int f1(int curr, vector<int> &dp, vector<int> &val){
    if(curr<1) return 0; // base case
    if(dp[curr]!=-1) return dp[curr]; // dp line

    return dp[curr] = max(val[curr] + f(curr-2, dp, val), f(curr-1, dp, val)); // all stuffs on index
}

int main(){
    int n; cin >> n;
    vector<int> dp(n,-1);
    vector<int> dp1(n,-1);
    vector<int> val(n);

    for(int i=0; i<n; i++){
        cin >> val[i];
    }

    if(n<1){
        cout << val[0] << endl;
        return 0;
    }

    // memoization
    cout << max(f1(n-1, dp1, val), f(n-2, dp, val)) << endl;
    
    // tabulation
    // dp[0] = val[0];
    // dp[1] = max(val[0], val[1]);
    // for(int i=2; i<n; i++){
    //     dp[i] = max(val[i] + dp[i-2], dp[i-1]);
    // }
    
    // cout << max(dp[n-1], dp[n-2]) << endl;

    // space optimization
    // int prev2 = val[0];
    // int prev1 = max(val[0], val[1]);
    // for(int i=2; i<n; i++){
    //     int curr = max(val[i] + prev2, prev1);
    //     prev2=prev1;
    //     prev1=curr;
    // }
    
    // cout << max(prev2, prev1) << endl;

    return 0;
}
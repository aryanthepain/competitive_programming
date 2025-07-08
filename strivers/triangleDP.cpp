#include <bits/stdc++.h>
using namespace std;
#define INF 1e9+9

int f(int curr, int i, vector<vector<int>> &dp, vector<vector<int>> &triangle){
    // base case
    if(curr>=triangle.size()) return INF;
    if(i>=triangle[i].size()) return INF;
    if(curr==triangle.size()-1) return dp[curr][i] = triangle[curr][i];

    // dp line
    if(dp[curr][i]!=-1) return dp[curr][i];

    // all stuffs
    return dp[curr][i] = triangle[curr][i] + min(f(curr+1, i, dp, triangle), f(curr+1, i+1, dp, triangle));
}

int main(){
    int n; cin >> n;
    vector<vector<int>> triangle;
    if(n) triangle= {{-10}};
    else triangle= {{2},{3,4},{6,5,7},{4,1,8,3}};

    n = triangle.size();
    // vector<vector<int>> dp(n, vector<int>(n, -1));

    // cout << f(0, 0, dp, triangle)<<endl;

    // tabulation
    // for(int j=n-1; j>=0; j--){
    //     for(int i=0; i<=j; i++){
    //         if(j==n-1) dp[j][i] = triangle[j][i];
    //         else dp[j][i] = triangle[j][i] + min(dp[j+1][i], dp[j+1][i+1]);
    //     }
    // }

    // cout<<dp[0][0];

    // space optimisation
    vector<int> dp(n,-1);
    for(int j=n-1; j>=0; j--){
        vector<int> temp(j+1, -1);
        for(int i=0; i<=j; i++){
            if(j==n-1) temp[i] = triangle[j][i];
            else temp[i] = triangle[j][i] + min(dp[i], dp[i+1]);
        }
        dp=temp;
    }

    cout<<dp[0];
}
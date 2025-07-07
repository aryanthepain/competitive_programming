#include <bits/stdc++.h>
using namespace std;
#define INF 1e9+9

int jump(int curr , vector<int> &cost, vector<int> &dp){
    if(dp[curr]!=-1) return dp[curr];

    int left=jump(curr-1, cost, dp) + abs(cost[curr]-cost[curr-1]);
    int right=jump(curr-2, cost, dp) + abs(cost[curr]-cost[curr-2]);

    return dp[curr] = min(left, right);
}

int main(){
    int n; cin >> n;
    vector<int> cost(n);

    for(int i=0; i<n; i++){
        cin >> cost[i];
    }

    vector<int> dp(n+1, -1);
    dp[0] = 0; // base case
    dp[1] = abs(cost[1]-cost[0]);

    cout << jump(n-1, cost, dp) << endl;
}
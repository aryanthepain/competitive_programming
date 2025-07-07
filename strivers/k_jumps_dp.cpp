#include <bits/stdc++.h>
using namespace std;
#define INF 1e9+9

int jump(int curr, int k, vector<int> &cost, vector<int> &dp){
    if(curr<0) return INF;
    if(dp[curr]!=-1) return dp[curr];

    int temp=INF;
    for(int i=1; i<k+1; i++){
        if(curr-i>=0)
            temp = min(temp, jump(curr-i, k, cost, dp) + abs(cost[curr]-cost[curr-i]));
    }

    return dp[curr] = temp;
}

int main(){
    int n, k; cin >> n >> k;
    vector<int> cost(n);

    for(int i=0; i<n; i++){
        cin >> cost[i];
    }

    vector<int> dp(n+1, -1);
    dp[0] = 0; // base case
    dp[1] = abs(cost[1]-cost[0]);

    cout << jump(n-1, k, cost, dp) << endl;

    return 0;
}
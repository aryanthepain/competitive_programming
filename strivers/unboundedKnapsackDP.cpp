#include <bits/stdc++.h>
using namespace std;
#define MINI -1e9

int f(int index, int wleft, vector<int> &val, vector<int> & weight, vector<vector<int>> &dp){
    // base case
    if(index==0){
        return (wleft/weight[index])*val[index];
    }
    if(wleft==0) return 0;

    // dp line
    if(dp[index][wleft]!=-1) return dp[index][wleft];

    // all stuffs
    int notTake= f(index-1, wleft, val, weight, dp);
    int take= MINI;
    if(weight[index]<=wleft) take = val[index] + f(index, wleft-weight[index], val, weight, dp);

    return dp[index][wleft] = max(take, notTake);
}

int main(){
    int x; cin>>x;
    vector<int> val;
    vector<int> wt;
    int W,n;

    if(x==0){
        val={5, 11, 13};
        wt = {2, 4, 6};
        W = 10;
        n = 3;
    } else{
        val={10, 40, 50, 70};
        wt = {1, 3, 4, 5};
        W = 8;
        n = 4;
    }

    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    cout << f(n-1, W, val, wt, dp);

    return 0;
}
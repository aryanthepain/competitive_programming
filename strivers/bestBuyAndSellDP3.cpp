#include <bits/stdc++.h>
using namespace std;

int f(int ind, int buy, int sale,vector<int> &prices, vector<vector<vector<int>>> &dp){
    // base case
    if(sale>1) return 0;
    if(ind==prices.size()) return 0;

    // dp line
    if(dp[ind][buy][sale]!=-1) return dp[ind][buy][sale];

    // all stuff
    if(buy){
        return dp[ind][buy][sale] = max(-prices[ind] + f(ind+1,0,sale,prices,dp), f(ind+1, 1, sale, prices, dp));
    } else{
        return dp[ind][buy][sale] = max(prices[ind] + f(ind+1, 1, sale, prices, dp), f(ind+1, 0, sale, prices, dp));
    }
}

int main(){
    int prof=0, n=prices.size();
    bool hs=false;
    for(int i=0; i<n-1; i++){
        if(hs){
            // always sell
            prof+=prices[i];
            hs=false;
        }

        if(prices[i]<prices[i+1]){
            hs=true;
            prof-=prices[i];
        }
    }
    // last day
    if(hs){
        prof+=prices[n-1];
    }

    return prof;
}
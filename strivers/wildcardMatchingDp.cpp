#include <bits/stdc++.h>
using namespace std;

bool f(int i, int j, string &s, string &p, vector<vector<int>> &dp){
    // base case
    if(i==0 && j==0) return true;
    if(i==0){
        for(int x=1; x<=j; x++){
            if(p[x-1]!='*') return false;
        }
        return true;
    }
    if(j==0) return false;
    
    // dp line
    if(dp[i][j]!=-1) return dp[i][j];

    // all stuffs
    if(p[j-1]=='*'){
        return dp[i][j] = f(i-1, j, s, p, dp) || f(i, j-1, s, p, dp);
    }

    if(p[j-1]==s[i-1] || p[j-1]=='?'){
        return dp[i][j] = f(i-1, j-1, s, p, dp);
    }
    
    return dp[i][j] = false;
}

int main(){
    int m=s.length(), n=p.length();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));

    // return f(s.length(), p.length(), s, p, dp);
    // base case
    dp[0][0]=true;
    int x=1;
    while(p[x-1]=='*'){
        dp[0][x]=true;
        x++;
    }

    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(p[j-1]=='*'){
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }

            if(p[j-1]==s[i-1] || p[j-1]=='?'){
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }

    return dp[m][n];
}
#define <bits/stdc++.h>
using namespace std;

int f(int curr, vector<int> &dp){
    if(curr<1) return 0;

    return dp[curr] = f(curr-1, dp) + f(curr-2, dp);
}

int main(){
    int n; cin >> n;

    vector<int> dp(n+1, -1);

    // base case
    dp[0]=0; dp[1]=1;
    cout << f(n, dp) << endl;

    return 0;
}
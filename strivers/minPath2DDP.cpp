#include <bits/stdc++.h>
using namespace std;
#define ll long long
# define INF 1e9+9
ll f(ll m, ll n, vector<vector<ll>> &dp, vector<vector<ll>> &space){
    // base case
    if(m<0 || n<0) return INF;
    // if(space[m][n]==1) return 0;
    if(m==0 && n==0) return space[0][0];

    // dp
    if(dp[m][n]!=-1) return dp[m][n];
    
    // all stuffs
    return dp[m][n] = space[m][n] + min(f(m-1,n,dp,space), f(m, n-1, dp,space));
}

int main(){
    int m, n; cin >> m >>  n;
    vector<vector<ll>> space(m, vector<ll>(n));

    // input vector
    for(ll i=0; i<m; i++){
        for(ll j=0; j<n; j++){
            cin>>space[i][j];
        }
    }

    vector<vector<ll>> dp(m, vector<ll>(n,-1));

    cout << f(m-1, n-1, dp, space) << endl;

    return 0;
}
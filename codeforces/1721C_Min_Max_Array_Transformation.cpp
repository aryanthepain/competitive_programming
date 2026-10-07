#include <bits/stdc++.h>
using namespace std;
#define ll long long

int lessgo();
int main(){
    int t; cin >> t;
    
    while(t--){
        lessgo();
    }

    return 0;
}

int lessgo(){
    ll n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);

    // input vectors
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    for(int i=0; i<n; i++){
        cin >> b[i];
    }
    
    // get the lowest value
    ll l=0;
    vector<ll> minPos(n);
    for(int i=0; i<n; i++){
        while(b[l]<a[i]){
            l++;
        }

        cout << (b[l]-a[i]) << " ";
        minPos[i] = l; // storing minimum possible position acceptable
    }
    cout << endl;

    // get the highest value
    vector<ll> ans(n);
    ll r= n-1;
    for(int i=n-1; i>=0; i--){
        ans[i]= b[r] - a[i];
        
        if(i==minPos[i]){
            r=minPos[i]-1;
        }
    }
    // printing highest vector
    for(int i=0; i<n; i++){
        cout << ans[i] << " ";
    }
    cout  << endl;

    return 0;
}
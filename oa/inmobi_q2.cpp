#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    // 1. Fast I/O for Online Assessments
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> r(n);
    int P;
    for (int i = 0; i < n; i++) {
        cin >> P >> r[i]; 
        // Note: P[i] is completely ignored in the logic below as requested by the prompt!
    }

    // khel khatam on start
    for(auto &x:r){
        if(2*x+1>=n){
            cout << 1 << endl;
            return 0;
        }
    }

    int maxp = 3*n;
    vector<int> jump(maxp+1);

    // minimum start of
    for(int i=0; i<maxp+1; i++){
        jump[i]=i;
    }
    
    // farthest jump
    for(int i=0; i<n; i++){
        for(int k=0; k<3; k++){
            int c = i + n*k;
            int l=max(0, c-r[i]);
            int rr=min(maxp, c+r[i]+1);

            if(l<maxp+1)
                jump[l]=max(jump[l], rr);
        }
    }

    // prefix jump
    for(int i=1; i<maxp+1; i++){
        jump[i]=max(jump[i], jump[i-1]);
    }

    // time machine
    int log = 20;
    vector<vector<int>> up(log, vector<int>(maxp+1));

    up[0] = jump;

    for(int k=1; k<log; k++){
        for(int i=0; i< maxp+1; i++){
            up[k][i] = up[k-1][up[k-1][i]];
        }
    }

    int ans=1e9;

    for(int i=0; i<n; i++){
        int curr=i;
        int target=curr+n;
        int steps=0;

        if(up[log-1][curr] < target) continue;

        for(int k=log-1; k>=0; k--){
            if(up[k][curr]<target){
                steps+= (1<<k);
                curr=up[k][curr];
            }
        }

        curr = jump[curr];
        steps++;

        if(curr < target) continue;

        ans=min(ans, steps);
    }


    
    if (ans > n) {
        cout << -1 << "\n"; // Should theoretically not trigger unless input is flawed
    } else {
        cout << ans << "\n";
    }
    
    return 0;
}
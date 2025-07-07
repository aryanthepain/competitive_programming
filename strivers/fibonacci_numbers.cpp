#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;

    int prev2=0, prev=1; // save in array in case multiple testcases

    for(int i=2; i<n+1; i++){
        int cur=prev2+prev;
        prev2=prev;
        prev=cur;
    }
    cout << prev << endl;

    return 0;
}
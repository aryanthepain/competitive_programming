#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;

    vector<int> arr(n);

    int xor2=0;

    for(int i=0; i < n; i++){
        cin >> arr[i];
        xor2^=arr[i]; // getting xor of all numbers
    }
    // right most set bit
    int mask = xor2^(xor2&(xor2-1));

    // bucketing based on right most set bit
    int x1=0, x2=0;
    for(int i=0; i < n; i++){
        if(arr[i] & mask){
            x1^=arr[i];
        } else {
            x2^=arr[i];
        }
    }

    if(x1 > x2) swap(x1,x2);

    cout << x1 << " " << x2 << endl;

    return 0;
}
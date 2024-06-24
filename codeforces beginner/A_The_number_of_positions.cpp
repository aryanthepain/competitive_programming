#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int a; cin >> a;
    int b; cin >> b;

    if((n-a-1)>b) cout << b+1 << endl;
    else cout << n-a << endl;

    return 0;
}
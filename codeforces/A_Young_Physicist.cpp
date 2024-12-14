#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int x=0; int y=0; int z=0; int a;

    for (int i = 0; i < n; i++)
    {
        cin >> a; x+=a;
        cin >> a; y+=a;
        cin >> a; z+=a;
    }
    
    if(x || y || z) cout << "NO" << endl;
    else cout << "YES";

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    string a; cin >> a;
    string str1="1111111";
    string str2="0000000";

    int found=-1;
    int found1=-1;
    found = a.find(str1);
    found1 = a.find(str2);
    // cout << found << endl;
    // cout << found1 << endl;
    if(found!=-1 || found1!=-1) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
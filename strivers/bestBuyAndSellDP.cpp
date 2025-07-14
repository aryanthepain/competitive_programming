#include <bits/stdc++.h>
using namespace std;


int main(){
    int mini=1e6, maxd=0, n=prices.size();
    for(int i=0; i<n; i++){
        mini=min(mini, prices[i]);
        maxd=max(maxd, prices[i]-mini);
    }

    return maxd;
}
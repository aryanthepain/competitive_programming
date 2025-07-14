#include <bits/stdc++.h>
using namespace std;


int main(){
    int prof=0, n=prices.size();
    bool hs=false;
    for(int i=0; i<n-1; i++){
        if(hs){
            // always sell
            prof+=prices[i];
            hs=false;
        }

        if(prices[i]<prices[i+1]){
            hs=true;
            prof-=prices[i];
        }
    }
    // last day
    if(hs){
        prof+=prices[n-1];
    }

    return prof;
}
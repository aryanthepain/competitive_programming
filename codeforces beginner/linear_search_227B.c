#include<stdio.h>

void inputarr(long long int n, int arr[n]){
    for(long long int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

int main(){
    long long int n;
    scanf("%lld", &n);
    int ar1[n];
    inputarr(n,ar1);
    int index[n+1];

    for (long long int i = 0; i < n; i++) {
        index[ar1[i]] = i;
        
    }

    long long int m;
    scanf("%lld", &m);
    int ar2[m];
    inputarr(m,ar2);

    long long int countf=0;

    for(long long int i=0; i<m; i++){
        countf+= index[ar2[i]] + 1;

    }

    printf("%lld ", countf);
    long long int countb=0;

    for(long long int i=0; i<m; i++){
        countb+=n-index[ar2[i]];

    }

    printf("%lld", countb);
    
    return 0;
}
#include<stdio.h>

int main(){
    long long int n, k;
    
    scanf("%lld", &n);
    scanf("%lld", &k);

    if(n%2==0 && k<=n/2){//even odd
        printf("%lld", 2*k-1);
    }
    else if(n%2==0 && k>n/2){//even even
        k=k-n/2;
        printf("%lld", 2*k);
    }
    else if(n%2==1 && k<=n/2+1){//odd odd
        printf("%lld", 2*k-1);
    }
    else if(n%2==1 && k>n/2+1){//even even
        k=k-n/2-1;
        printf("%lld", 2*k);
    }

    return 0;
}
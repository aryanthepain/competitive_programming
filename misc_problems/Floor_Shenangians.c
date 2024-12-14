#include<stdio.h>

void function(){
    long long int n;
    long long int k;
    long long int count=0;

    scanf("%lld", &n);
    scanf("%lld", &k);

    while(n>0){
        if(n%k==0){
            n=n/k;
            count++;
        }
        else{
            n-=1;
            count++;
        }
    }
    printf("%lld\n", count);
}

int main(){
    int t;

    scanf("%d", &t);

    for(int i=0; i<t; i++){
        function();
    }

    return 0;
}
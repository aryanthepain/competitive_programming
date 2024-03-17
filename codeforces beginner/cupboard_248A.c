#include<stdio.h>

int main(){
    int n, t=0;
    scanf("%d", &n);
    int l[n], r[n];
    int lo=0,ro=0;//no of ones

    //input array
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        l[i]=a;
        scanf("%d", &a);
        r[i]=a;
    }

    for(int i=0; i<n; i++){
        if(l[i]){
            lo++;
        }
        if(r[i]){
            ro++;
        }
    }

    if(lo<=n/2){
        t=t+lo;
    }
    else{
        t=t+n-lo;
    }
    if(ro<=n/2){
        t=t+ro;
    }
    else{
        t=t+n-ro;
    }

    printf("%d", t);

    return 0;
}
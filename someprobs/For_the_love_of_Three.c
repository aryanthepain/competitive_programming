#include<stdio.h>

void function(){
    long long int n;
    scanf("%lld", &n);
    long long int arr[n];
    long long int count=0;

    for(long long int i=0; i<n; i++){
        scanf("%lld", &arr[i]);
    }

    long long int onecount=0;
    long long int twocount=0;
    for(long long int j=0; j<n; j++){
        long long int a;
        a=arr[j]%3;
        if(a==0){
            count++;
        }
        else if(a==1){
            onecount++;
        }
        else if(a==2){
            twocount++;
        }
    }
    // printf("%d %d\n", onecount, twocount);
    if(onecount>=twocount){
        count+=twocount;
        onecount-=twocount;
        count+=(onecount/3);
    }
    else{
        count+=onecount;
        twocount-=onecount;
        count+=twocount/3;
    }
    // printf("%d %d\n", onecount, twocount);
    printf("%d\n", count);
}

int main(){
    int t;

    scanf("%d", &t);

    for(int i=0; i<t; i++){
        function();
    }

    return 0;
}
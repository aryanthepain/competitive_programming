#include<stdio.h>

void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        arr[i]=a;
    }
}

int main(){
    int n;//no of pages
    scanf("%d", &n);

    int arr[7];
    inputarr(7, arr);

    int i=0;
    for(i; i<=7; i++){
        if(n<=0){//last day
            break;
        }
        if(i==7){//new week
            i=0;
        }
        n=n-arr[i];
    }

    printf("%d", i);

    return 0;
}
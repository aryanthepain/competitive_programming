#include<stdio.h>

void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

void diffarr(int n, int arr[n], int diff[n]){
    for(int i=0; i<n-1; i++){
        int a=arr[i]-arr[i+1];
        if(a<0){
            a=-1*a;
        }
        diff[i]=a;
    }
    int a=arr[n-1]-arr[0];
    if(a<0){
        a=-1*a;
    }
    diff[n-1]=a;
}

int minarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a>arr[i]){
            a=arr[i];
        }
    }
    for(int i=0; i<n; i++){
        if(a==arr[i]){
            return i;
        }
    }
    return a;
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    int diff[n];
    inputarr(n, arr);

    diffarr(n, arr, diff);

    int min=minarr(n, diff);

    if(min==n-1){
        printf("%d 1", n);
    }
    else{
        printf("%d %d", min+1, min+2);
    }

    return 0;
}
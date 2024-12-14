#include<stdio.h>

void inputarr(int n,int arr[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

int maxarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a<arr[i]){
            a=arr[i];
        }
    }
    return a;
}

int main(){
    //inputs
    int n,m;
    scanf("%d", &n);
    int ar1[n];
    inputarr(n,ar1);
    scanf("%d", &m);
    int ar2[m];
    inputarr(m,ar2);
    int arr[m*n];//ratio Matrix
    for(int i=0; i<m*n; i++){
        arr[i]=0;
    }
    
    int i=0;
    for(int j=0; j<n; j++){
        for(int k=0; k<m; k++){
            if(ar2[k]%ar1[j]==0){
               arr[i]=ar2[k]/ar1[j];
               i++;
            }
        }
    }
    
    int a=maxarr(i,arr);
    int count=0;
    
    for(int j=0; j<i; j++){
        if(arr[j]==a){
            count++;
        }
    }
    
    printf("%d", count);
    
    return 0;
}
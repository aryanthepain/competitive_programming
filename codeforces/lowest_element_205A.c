#include<stdio.h>

void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

int minarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a>arr[i]){
            a=arr[i];
        }
    }
    return a;
}

int posarr(int n, int arr[n]){
    int a=minarr(n,arr);
    int count=0;
    int pos;
    for(int i=n-1; i>=0; i--){
        if(arr[i]==a){
            count++;
            pos=i;
        }
    }
    if(count==1){
        return pos+1;
    }
    else{
        return -1;
    }
} 

int main(){
    int n;
    scanf("%d", &n);

    int arr[n];
    inputarr(n, arr);

    int pos=posarr(n,arr);
    if(pos==-1){
        printf("Still Rozdil");
    }
    else{
        printf("%d", pos);
    }

    return 0;
}
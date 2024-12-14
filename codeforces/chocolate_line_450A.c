#include<stdio.h>

void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        arr[i]=a;
    }
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int arr[n];
    inputarr(n, arr);

    for(int i=0; i>=0; i++){
        int count=0;
        int last;
        for(int j=0; j<n; j++){
            if(arr[j]>0){
                last=j+1;
            }
            arr[j]-=m;
            if(arr[j]>0){
                count++;
            }
        }
        if(count==0){
            printf("%d", last);
            return 0;
        }
    }

    return 0;
}
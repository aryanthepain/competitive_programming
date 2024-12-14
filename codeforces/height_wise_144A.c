#include<stdio.h>

int main(){
    int n, t=0;
    scanf("%d", &n);
    int arr[n];
    int large=0, small=0;

    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        arr[i]=a;
    }

    for(int i=0; i<n; i++){
        if(arr[i]<=arr[small]){
            small=i;
        }
    }
    int smallest=arr[small];

    while(arr[n-1]!=smallest){
        int temp=arr[small+1];
        arr[small+1]=arr[small];
        arr[small]=temp;
        small++;
        t++;
    }

    for(int i=n-1; i>=0; i--){
        if(arr[i]>=arr[large]){
            large=i;
        }
    }

    int largest=arr[large];

    while(arr[0]!=largest){
        int temp=arr[large+1];
        arr[large-1]=arr[large];
        arr[large]=temp;
        large--;
        t++;
    }

    printf("%d", t);

    return 0;
}
#include<stdio.h>

void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int arr[m];
    inputarr(m, arr);

    long long int count=0;
    int pos=1;

    for(int i=0; i<m;){
        if(pos==arr[i]){
            i++;
        }
        else if(pos<arr[i]){
            count+=arr[i]-pos;
            pos=arr[i];
        }
        else if(pos>arr[i]){
            count+=n-pos+arr[i];
            pos=arr[i];
        }
    }

    printf("%lld", count);

    return 0;
}
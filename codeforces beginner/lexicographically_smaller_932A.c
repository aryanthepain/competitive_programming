#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        long long int x;
        scanf("%lld", &x);
        char arr[100];
        int count=0;
        scanf("%s", &arr);
        for (int k = 0; k < 100; k++){
            count++;
            if(arr[k]<97 || arr[k]>122){
                break;
            }
        }
        int a=(int)arr[0];
        int b=(int)arr[count-2];
        if(a<=b){
            for(int j=0; j<count-1; j++){
                printf("%c", arr[j]);
                if(arr[j]<97 || arr[j]>122){
                break;
                }
            }
        }
        else{
            for(int j=count-1; j>=0; j--){
                printf("%c", arr[j]);
            }
            for(int j=0; j<count-1; j++){
                printf("%c", arr[j]);
                if(arr[j]<97 || arr[j]>122){
                break;
                }
            }
        }
    }

    return 0;
}
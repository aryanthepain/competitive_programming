#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);

    if(n==1){
        printf("-1");
        return 0;
    }
    else{
        for(int i=2; i<=n; i++){
            printf("%d ", i);
        }

        printf("1");
    }

    return 0;
}
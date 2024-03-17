#include<stdio.h>

int main(){
    long long int a, b, n;
    scanf("%lld", &a);
    scanf("%lld", &b);
    scanf("%lld", &n);

    /*if(a==3 && b==40 && n==1){
        printf("-1");
        return 0;
    }*/

    for(int i=0; i<n; i++){
        a=a*10;
        for(int j=0; a%b!=0; a++, j++){
            if(j==9){
                printf("-1");
                return 0;
            }
        }
        if(a%10==0){
            printf("%d", a/10);
            for(int k=i; k<n;k++){
                printf("0");
            }
            return 0;
        }
    }

    printf("%d", a);

    return 0;
}
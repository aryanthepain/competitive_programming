#include<stdio.h>

int main(){
    float n;
    float drink;
    float sum=0;

    scanf("%f", &n);//no of drinks

    for(int i=1; i<=n; i++){
        scanf("%f", &drink);
        sum=sum+drink;
    }

    printf("%f", sum/n);

    return 0;
}
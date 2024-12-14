#include<stdio.h>

int main(){
    int n;//no of friends
    scanf("%d", &n);
    int count=0;
    int sum=0;

    for(int i=1; i<=n; i++){
        int a;
        scanf("%d", &a);
        sum+=a;
    }

    for(int i=1; i<=5; i++){
        int a=sum + i;
        if((a-1)%(n+1)!=0){
            count++;
        }
    }

    printf("%d", count);


    return 0;
}
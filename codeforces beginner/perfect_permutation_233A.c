#include<stdio.h>

int main(){
    int n;

    scanf("%d", &n);

    if(n%2==0){
        for(int i=2; i<=n; i+=3){
            printf("%d ", i);
            i--;
            printf("%d ", i);
        }
    }

    else printf("-1");

    return 0;
}
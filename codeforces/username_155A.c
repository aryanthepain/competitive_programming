#include<stdio.h>

int main(){
    int n, temp;
    scanf("%d", &n);
    int count=0;
    scanf("%d", &temp);
    int largest=temp;
    int smallest=temp;

    for(int i=2; i<=n; i++){
        int a;
        scanf("%d", &a);

        if(a>largest){
            count++;
            largest=a;
        }
        if(a<smallest){
            count++;
            smallest=a;
        }
    }

    printf("%d", count);

    return 0;
}
#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int max=0, count=0;

    for(int i=1; i<=n; i++){
        int a;
        scanf("%d", &a);
        count=count-a;
        scanf("%d", &a);
        count=count+a;
        
        if(count>max){
            max=count;
        }
    }

    printf("%d", max);

    return 0;
}
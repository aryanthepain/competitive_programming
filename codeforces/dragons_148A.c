#include<stdio.h>

int main(){
    int d;//total dragons
    int k, l, m, n; //no of ways to beat
    int count=0;//total beaten dragons

    //inputs
    scanf("%d", &k);
    scanf("%d", &l);
    scanf("%d", &m);
    scanf("%d", &n);
    scanf("%d", &d);

    for(int i=1; i<=d; i++){
        if(i%k!=0 && i%l!=0 && i%m!=0 && i%n!=0){//check if any position dragon is divisible by klmn
            count++;//if position is not divisible by klmn
        }
    }

    printf("%d",d-count);

    return 0;
}
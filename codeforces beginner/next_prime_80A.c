#include<stdio.h>

int isPrime(int a){//check if a number is prime
    if(a==1){
        return 0;
    }
    for(int i=2; i*i<=a; i++){
        if(a%i==0){
            return 0;
        }
    }

    return 1;
}

int main(){
    printf("To check if the second number is next prime to second number\n=================\nEnter the first number:");
    int tod, nxt;
    scanf("%d", &tod);
    printf("Enter the second number:");
    scanf("%d", &nxt);

    for(int i=tod+1; i<=nxt; i++){//check for prime number after first number
        if(isPrime(i)){
            if(i==nxt){
                printf("YES");
            }
            else{
                printf("NO");
            }
            return 0;
        }
    }

    printf("NO");

    return 0;
}
#include<stdio.h>
 
int main(){
    long long int n;
    int digit, x;
    int count=0;
 
    scanf("%lld", &n);//input
 
    do{//checks number of 4 and 7
        digit=n%10;
        if(digit==7 || digit==4){
            count++;
        }
        n=n/10;
    }while(n!=0);
 
    do{//checks for 4 and 7
        digit=count%10;
        if(digit!=7 && digit!=4){
            x=0;//if not lucky-x=0
        }
        count=count/10;
    }while(count!=0);
 
    if(x==0)
        printf("NO");
    else if(x!=0)
        printf("YES");
 
    return 0;
}
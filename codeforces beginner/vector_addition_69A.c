#include <stdio.h>

int main(){
    printf("To check if given vectors are in equilibrium or not\n====================\n");
    
    int n, input, limit,x,y,z;

    //sum of the 3 components
    x=0;
    y=0;
    z=0;

    printf("enter the number of vectors:");

    scanf("%d", &n);//input

    limit=3*n;//total inputs

    printf("enter the vectors:\n");
    
    for(int i=1; i<=limit; i++){//loop inputs value one by one and adds them to respective components
        scanf("%d", &input);
        //x component
        if(i%3==0){
            x=x+input;
        }
        //y comp
        if(i%3==1){
            y=y+input;
        }
        //z comp
        if(i%3==2){
            z=z+input;
        }
    }

    // all three zero
    if(x==0 && y==0 && z==0){
        printf("YES, they are in equilibrium");
    }
    else{
    printf("NO, they are not in equilibrium");
    }

    return 0 ;
}

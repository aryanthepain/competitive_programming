#include<stdio.h>
#include<math.h>

int main(){
    int ab, bc, ca;
    scanf("%d", &ab);
    scanf("%d", &bc);
    scanf("%d", &ca);

    double asq=ab*ca/bc;
    double bsq=ab*bc/ca;
    double csq=bc*ca/ab;

    int a=sqrt(asq);
    int b=sqrt(bsq);
    int c=sqrt(csq);

    printf("%d", (a+b+c)*4);

    //124200,75,18,92

    return 0;
}
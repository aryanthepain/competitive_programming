#include<stdio.h>

int main(){
    char arr[100];//input array
    int n=0;//output array size

    for(int i=0; i<100; i++){
        char a;
        scanf("%c", &a);
        if(a!=49 && a!=50 && a!=51 && a!=43){
            break;
        }
        arr[i]=a;
        n++;
    }

    int m=(n+1)/2;
    char op[m];//sorting matrix

    //map op
    for(int i=0; i<m;i++){
        op[i]=arr[2*i];
    }

    //sort op
    for(int i=0; i<m-1; i++){
        if(op[i]>op[i+1]){
            char temp=op[i];
            op[i]=op[i+1];
            op[i+1]=temp;
            i=-1;
        }
    }

    //print sorted array
    printf("%c", op[0]);
    for(int i=1; i<m; i++){
        char a;
        a=op[i];
        printf("+");
        printf("%c", a);
    }
    
    return 0;
}
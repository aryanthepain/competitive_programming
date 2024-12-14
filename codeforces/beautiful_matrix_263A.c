#include<stdio.h>

int main(){
    printf("to check how many transformations it takes to make a 5X5 matrix beautiful\n===================\n");
    int i,onecount, zerocount,n;
    i=1;
    zerocount=0;
    printf("enter the matrix:\n");
    do{
        scanf("%d", &n);
        i++;
        if(n==0){
            zerocount++;//number of zeroes before 1
        }
        if(n==1){
            onecount=zerocount+1; //saves value of position of one
        }
    }while(i<26);
    // printf("%d\n", count);
    switch(onecount){//checks one's postion and gives output
        case 1:
            printf("4");
            break;
        case 2:
            printf("3");
            break;
        case 3:
            printf("2");
            break;
        case 4:
            printf("3");
            break;
        case 5:
            printf("4");
            break;
        case 6:
            printf("3");
            break;
        case 7:
            printf("2");
            break;
        case 8:
            printf("1");
            break;
        case 9:
            printf("2");
            break;
        case 10:
            printf("3");
            break;
        case 11:
            printf("2");
            break;
        case 12:
            printf("1");
            break;
        case 13:
            printf("0");
            break;
        case 14:
            printf("1");
            break;
        case 15:
            printf("2");
            break;
        case 16:
            printf("3");
            break;
        case 17:
            printf("2");
            break;
        case 18:
            printf("1");
            break;
        case 19:
            printf("2");
            break;
        case 20:
            printf("3");
            break;
        case 21:
            printf("4");
            break;
        case 22:
            printf("3");
            break;
        case 23:
            printf("2");
            break;
        case 24:
            printf("3");
            break;
        case 25:
            printf("4");
            break;
    }

    return 0;
}
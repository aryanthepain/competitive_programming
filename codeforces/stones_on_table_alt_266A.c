#include<stdio.h>

int main(){
    printf("To print an array such that no two concurrent letters are same by removing one of the same letters\n=================\nEnter the number of letters in the array:");
    int n;
    int i=0;
    scanf("%d", &n);

    printf("Enter the array:");

    char arr[n+1];
    scanf("%s", arr);
    arr[n+1]=0;

    while(i<n){
        if(arr[i]==0){//break upon ending
            break;
        }
        if(arr[i]==arr[i+1]){//check if two concurrent are same
            for(int j=i+1;j<n;j++){//shift all next letters one step back
                arr[j]=arr[j+1];                
            }
            n--;
        }
        i++;
    }

    for(int i=0; i<n; i++){//print the output
        if(arr[i]==0){
            break;
        }
        char c=arr[i];
        printf("%c", c);
    }

    return 0;
}
#include<stdio.h>
 
int main(){
    printf("To count the minimum number of lettera to take from the array so that any two neighboring letters are different\n==============\nEnter the number of letters in array:");
    int n;
    int i=0, count=0;
    scanf("%d", &n);

    printf("Enter the array:"); 
    char arr[n+1];
    arr[n]=0;
    scanf("%s", arr);
 
    while(i<n){
        if(arr[i]==arr[i+1]){
            count++;
        }
        i++;
    }
 
    printf("%d letters need to be removed", count);
 
    return 0;
}
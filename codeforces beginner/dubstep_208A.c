#include<stdio.h>

int main(){
    char arr[200];
    for(int i=0; i<200; i++){
        arr[i]=0;
    }

    scanf("%s", arr);
    int count=1;

    for(int i=0; i<200; i++){
        if(arr[i]==0){
            break;
        }
        if(arr[i]=='W' && arr[i+1]=='U' && arr[i+2]=='B'){
            i+=2;
            if(count==0){
                printf(" ");
            }
            count+=1;
            continue;
        }
        else{
            count=0;
        }
        printf("%c", arr[i]);
    }

    return 0;
}
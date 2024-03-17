#include<stdio.h>
#include<string.h>

int main(){
    int n,t;

    printf("Check the order of a boy and girl queue when boys are chivalrous\n===================\nenter the number of students:");

    scanf("%d",&n);
    printf("enter the time after which you want to see the queue:");
    scanf("%d",&t);    
    
    printf("enter the starting order of the queue:\n");
    char arr[n+1];
    scanf("%s", arr);
    
    for(int j=1; j<=t; ++j){//time counter
        for(int i=1; i<n;++i){//position counter
            if(arr[i-1]=='B' && arr[i]=='G'){//convert 'BG' to 'GB'
                //switch adjacent boys and girls
                arr[i]='B';
                arr[i-1]='G';
                i=i+1;//skip next position as it is already exchanged
            }
        }
    }

    printf("%s",arr);

    return 0;
}
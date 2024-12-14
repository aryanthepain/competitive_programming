#include<stdio.h>
#include<string.h>

int main(){
    printf("To find a beautiful year(all digits are different) after the given year\n===============\nenter the year:");
    int n;

    scanf("%d", &n);

    for(int i=n+1; i<10000; i++){//year counter
        int x=0;//match counter
        int arr[4]={i % 10, (i / 10) % 10, (i / 100) % 10, (i / 1000) % 10};
        int j=0;//digit counter
        do{
            int k=1;//next digits counter
            do{
                if(arr[j]==arr[j+k]){
                    x=1;
                }
                k++;
            }while (j+k<4);
            j++;
            if(x==1){
                break;
            }
        }while(j<3);
        if(x==0){
            printf("%d", i);
            break;
        }
    }

    return 0;
}
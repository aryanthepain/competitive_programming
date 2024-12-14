#include<stdio.h>
#include<string.h>

int main(){
    char a[100], b[100];

    scanf("%s", a);

    scanf("%s", b);

    for(int i=0; i<100; i++){
        if(a[i]=='\000'){
            break;
        }
        if(a[i]==b[i]){
            printf("0");
        }
        else printf("1");
    }

    return 0;
}
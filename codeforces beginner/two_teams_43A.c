#include<stdio.h>
#include<string.h>

void inputarr(int n, char arr[][11]){ // Changed to [11] to accommodate 10 characters + '\0'
    for(int i=0; i<n; i++){
        scanf("%s", arr[i]);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    char arr[n][11]; // Changed to [11] to accommodate 10 characters + '\0'
    inputarr(n, arr);

    char a[11], b[11]; // Changed to [11] to accommodate 10 characters + '\0'
    strcpy(a,arr[0]);

    // Finding other team
    for(int i=1; i<n; i++){
        if(strcmp(a,arr[i]) != 0){ // Check for inequality
            strcpy(b,arr[i]);
            break;
        }
    }
    int acount=0, bcount=0;
    for(int i=0; i<n; i++){
        if(strcmp(arr[i], a)==0){
            acount++;
        }
        else if(strcmp(arr[i], b)==0){
            bcount++;
        }
    }

    if(acount>bcount){
        printf("%s\n", a); // Added '\n' after printf()
    }
    else{
        printf("%s\n", b); // Added '\n' after printf()
    }
    
    return 0;
}

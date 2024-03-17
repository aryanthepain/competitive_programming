#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char arr[200];
    scanf("%s", arr);
    
    for (int i = 0; i < strlen(arr); i++) {
        if (arr[i] == '.') {
            printf("0");
        } else if (arr[i] == '-') {
            i++;  // Move to the next character after the dash
            if (arr[i] == '.') {
                printf("1");
            } else if (arr[i] == '-') {
                printf("2");
            }
        }

        //to get out of the loop when string ends
        if (isspace(arr[i + 1])) {
            break;
        }
    }

    return 0;
}

#include<stdio.h>
#include<ctype.h>

int main(){
    printf("To capitalise a word properly\n===================\nEnter the word:\n");
    char arr[1000];

    scanf("%s", arr);//input

    //65-90=capital letters
    //97-122=small letters
    //difference=32
    
    int ascii;//ascii code
    int i=0;

    ascii=(int)arr[0];
    if(ascii>=95 && ascii<=122){   //else convert to large if needed
    ascii -= 32;
    }
    printf("%c", ascii);

    for(int pos=1; pos<1000; pos++){
        if(arr[pos]==0){    //break code at space
            break;
        }

        ascii= (int) arr[pos];  //ascii code converter

        if(ascii>=65 && ascii<=90){     //convert to small if needed
        ascii += 32;
        }
       
        printf("%c", ascii);
    }

    return 0;
}
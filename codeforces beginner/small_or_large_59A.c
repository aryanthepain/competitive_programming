#include<stdio.h>
#include<ctype.h>

int main(){
    printf("To print a given word as all small or all caps based on which is more\n=======================\nEnter the word:\n");
    char arr[100];

    scanf("%s", arr);//input

    //65-90=capital letters
    //97-122=small letters
    //difference=32
    
    int largecount=0,smallcount=0, x;//j=large/k=small counters,x=which wins
    int ascii;//ascii code
    int i=0;

    for(int pos=0; pos<100; pos++){//to check which one is more, smaller or larger
        ascii = (int) arr[pos];//ascii code converter

        if(arr[pos]==0){    //break code at space
            break;
        }

        if(ascii<=90 && ascii>=65){     //large counter
            largecount++;
        }
        if(ascii>=97 && ascii<=122){    //small counter
            smallcount++;
        }
    }
    

    if(smallcount >= largecount)
        x=1;    //all small needed
    if(smallcount < largecount)
        x=0;    //all large needed

    for(int pos=0; pos<100; pos++){
        if(arr[pos]==0){    //break code at space
            break;
        }

        ascii= (int) arr[pos];  //ascii code converter

        if(ascii>=65 && ascii<=90 && x==1){     //convert to small if needed
        ascii += 32;
        }
        else if(ascii>=95 && ascii<=122 && x==0){   //else convert to large if needed
        ascii -= 32;
        }
       
        printf("%c", ascii);
    }

    return 0;
}
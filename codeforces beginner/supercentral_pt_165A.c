#include<stdio.h>

void inputarr(int n, int ar1[n], int ar2[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &ar1[i]);
        scanf("%d", &ar2[i]);
    }
}

int maxarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a<arr[i]){
            a=arr[i];
        }
    }
    return a;
}

int minarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a>arr[i]){
            a=arr[i];
        }
    }
    return a;
}

int main(){
    int n;
    scanf("%d", &n);
    int x[n];
    int y[n];
    int count=0;

    //inputting positions
    inputarr(n, x, y);

    //maximum size of grid array required
    int maxx=maxarr(n, x);
    int maxy=maxarr(n,y);
    int minx=minarr(n, x);
    int miny=minarr(n, y);
    
    for(int i=0; i<n; i++){
        int a=0;

        if(x[i]==minx || x[i]==maxx || y[i]==miny || y[i]==maxy){
            continue;
        }

        //right neighbour
        for(int j=0; j<n; j++){
            //same position
            if(x[j]==x[i] && y[j]==y[i]){
                continue;
            }

            if(x[j]>x[i] && y[j]==y[i]){
                a++;
                break;
            }
        }
        if(a==0){
            continue;
        }
        
        //left neighbour
        for(int j=0; j<n; j++){
            //same position
            if(x[j]==x[i] && y[j]==y[i]){
                continue;
            }

            if(x[j]<x[i] && y[j]==y[i]){
                a++;
                break;
            }
        }
        if(a==1){
            continue;
        }

        //lower neighbour
        for(int j=0; j<n; j++){
            //same position
            if(x[j]==x[i] && y[j]==y[i]){
                continue;
            }

            if(x[j]==x[i] && y[j]>y[i]){
                a++;
                break;
            }
        }
        if(a==2){
            continue;
        }

        //upper neighbour
        for(int j=0; j<n; j++){
            //same position
            if(x[j]==x[i] && y[j]==y[i]){
                continue;
            }

            if(x[j]==x[i] && y[j]<y[i]){
                a++;
                break;
            }
        }
        if(a==3){
            continue;
        }
        count++;
    }

    printf("%d", count);

    return 0;
}
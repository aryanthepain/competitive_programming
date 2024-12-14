//print an array

//character array
void printarr(int n, char arr[n]){
    for(int i=0; i<n; i++){
        char a;
        a=arr[i];
        printf("%c", a);
    }
}

//int array
void printarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        int a;
        a=arr[i];
        printf("%d", a);
    }
}
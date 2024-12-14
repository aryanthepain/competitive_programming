//input an array

//character array
void inputarr(int n, char arr[n]){
    for(int i=0; i<n; i++){
        char a;
        scanf("%s", &a);
        arr[i]=a;
    }
}

//int array
void inputarr(int n, int arr[n]){
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}
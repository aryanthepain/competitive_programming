int minarr(int n, int arr[n]){
    int a=arr[0];
    for(int i=1; i<n; i++){
        if(a>arr[i]){
            a=arr[i];
        }
    }
    return a;
}
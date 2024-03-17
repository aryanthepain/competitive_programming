for(int i=0; i<m-1; i++){
    if(x[i]>x[i+1]){
        char temp=x[i];
        x[i]=x[i+1];
        x[i+1]=temp;
        i=-1;
    }
}
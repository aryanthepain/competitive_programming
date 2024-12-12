//to check if a number is prime, output=1 if prime, else 0

int isprime(int a){
    if(a==1){
        return 0;
    }
    for(int i=2; i*i<=a; i++){
        if(a%i==0){
            return 0;
        }
    }

    return 1;
}
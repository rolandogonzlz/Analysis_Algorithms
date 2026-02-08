// Iterative Fibonacci function

#include <iostream>

void fibonacci_iter(int n){

    long long a = 0; //F(0) 
    long long b = 1; //F(1)

    for (int i =0; i<= n; i++){
        if (i == 0){
            std::cout <<a;
        }else if (i == 1){
            std::cout<<" "<<b;
        }else{
            long long c = a + b; //F(i) = F(i-1) + F(i-2)
            std::cout<<" "<<c;
            a = b;
            b = c;
        }

    }
    std::cout<<std::endl;
}

int main(){
    int n;
    std::cout<<"Enter the number of Fibonacci numbers to generate: ";
    std::cin>>n;

    if (n<0){
        std::cout<<"n must be >= 0"<<std::endl;
        return 0;
    }

    std::cout<<"Fibonacci sequence (iterative) up to F("<<n<<"):"<<std::endl;
    fibonacci_iter(n);

    return 0;
}
// recuenrsive fibonacci

#include <iostream>

long long fib_recursive(int n){
    if (n==0) return 0;          // F(0)
    if (n==1) return 1;          // F(1)
    return fib_recursive(n-1) + fib_recursive(n-2); // F(n) = F(n-1) + F(n-2)

}

void fibonacci_recursive_sequence(int n){
    for (int i= 0; i<= n; i++){
        std::cout<<fib_recursive(i)<<" ";
        if(i < n) std::cout<<" ";
    }
    std::cout<<std::endl;
}

int main(){
    int n;
    std::cout<<"Enter the number of Fibonacci numbers to generate: ";
    std::cin>>n;

    if(n <0){
        std::cout<<"n must be >= 0"<<std::endl;
        return 0;
    }

    std::cout<<"Fibonacci sequence (recursive) up to F("<<n<<"):"<<std::endl;
    fibonacci_recursive_sequence(n);
}
// Is it posiible to exchange numeric values of two varaibles, say, u and v, without using any extra storage?
// Show how with a program.

#include <iostream>

int main(){
    int u , v;
    std::cout<<"Enter the first number of u: ";
    std::cin>>u;

    std::cout<<"Enter the second number of v: ";
    std::cin>>v;

    // For to exchange the values of u and v, we can use the following code:
    std::cout<<"Before exchange:\nu = "<<u<<" and v: "<<v<<std::endl;

    u = u + v;
    v = u - v;
    u = u - v;

    std::cout<<"After exchange: \nu = "<<u<<" and v: "<<v<<std::endl;
    return 0;
}
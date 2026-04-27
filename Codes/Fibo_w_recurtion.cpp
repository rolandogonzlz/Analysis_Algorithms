//Create a C++ program that finds the nth Fibonacci number with recursion (No Dynamic
//Programming).

#include <iostream>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 0) { // base case
        return 0;
    }

    if (n == 1 || n == 2) { //if n is 1 or 2, return 1
        return 1;
    }

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;

    cout << "Enter n: ";
    cin >> n;

    cout << "Fibonacci number at position " << n << " is: "
         << fibonacciRecursive(n) << endl;

    return 0;
}
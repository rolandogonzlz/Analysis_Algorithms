//  The program does NOT work in the current form. Debug the program and make it work as
//expected.
#include <iostream>
#include <vector>
using namespace std;

int fibonacciDP(int n, vector<int>& memo) {
    if (n <= 0) {
        return 0;
    }

    if (memo[n] != -1) {
        return memo[n];
    }

    if (n == 1 || n == 2) {
        memo[n] = 1;
    } else {
        memo[n] = fibonacciDP(n - 1, memo) + fibonacciDP(n - 2, memo);
    }

    return memo[n];
}

int main() {
    int n;

    cout << "Enter n: ";
    cin >> n;

    vector<int> memo(n + 1, -1);

    cout << "Fibonacci number at position " << n << " is: "
         << fibonacciDP(n, memo) << endl;

    return 0;
}
#include <iostream>

int main(){
    // array of sequencial search
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // array of 10 elements
    // search key to find
    int key = 16; // key to find
    // size of the array
    int n = sizeof(arr) / sizeof(arr[0]); // size of the array
    // sequencial search algorithm
    int i = 0; // index to traverse the array
    while (i < n and arr[i] != key)
    {
        i = i + 1; // move to the next index
    }
    if (i < n ){
        std::cout << "Element found at index: " << i << std::endl; // element found
    } else {
        std::cout << "Element not found in the array." << std::endl; // element not found
    }
}
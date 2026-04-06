//Implement an algorithm to transform a random array into a heap

#include <iostream>
#include <vector>

//this function prints the elements of an array in a readable format
void imprimirArreglo(std::vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

//this function takes an array, its size, and an index as input and ensures that the subtree rooted at the given index satisfies 
//the max-heap property. It compares the value at the current index with its left and right children and swaps it with the largest value if necessary. 
//The function then recursively heapifies the affected subtree to maintain the max-heap property throughout the entire tree.
void heapify(std::vector<int>& arr, int n, int i) {
    int greater = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[greater]) {
        greater = left;
    }

    if (right < n && arr[right] > arr[greater]) {
        greater = right;
    }

    if (greater != i) {
        int temp = arr[i];
        arr[i] = arr[greater];
        arr[greater] = temp;

        heapify(arr, n, greater);
// this line recursively calls the heapify function on the affected subtree to ensure that the max-heap property is maintained throughout the entire tree after the swap.
    }
}

//this function takes an array as input and transforms it into a max-heap. It starts from the last non-leaf node and calls the heapify function for each node up to the root node.
void construirHeap(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int main() {
    std::vector<int> arr = {4, 10, 3, 5, 1, 8, 2};

    std::cout << "Original Array:" << std::endl;
    imprimirArreglo(arr);

    construirHeap(arr);

    std::cout << "Array converted into max-heap:" << std::endl;
    imprimirArreglo(arr);

    return 0;
}
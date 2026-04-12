// Implement the ComparisonCountingSort algorithm and test it

#include <iostream>

//This function sorts the array using the comparison counting sort algorithm
void comparisonCountingSort(int arr[], int n) {
    int* count = new int[n]; // count[i] is the number of elements less than arr[i]
    int* sorted = new int[n]; // sorted[i] is the i-th smallest element in arr

    for (int i = 0; i < n; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                count[j]++;
            } else {
                count[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++) { // Counting sort
        sorted[count[i]] = arr[i];
    }

    std::cout << "sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;

    delete[] count;
    delete[] sorted;
}

int main() {
    int arr[] = {62, 31, 84, 96, 19, 47};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "original array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    comparisonCountingSort(arr, n);

    return 0;
}
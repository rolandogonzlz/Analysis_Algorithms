// Implement the DistributionCountingSort algorithm and test it. Compare it with the
//ComparisonCountingSort from previous point. What are the differences of complexity and
//implementation?

#include <iostream>

//This function sorts the array using the distribution counting sort algorithm
void distributionCountingSort(int arr[], int n) {
    int minVal = arr[0];
    int maxVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i]; // Find the minimum value in the array
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    int range = maxVal - minVal + 1;
    int* count = new int[range]; // count[i] is the number of elements less than arr[i]

    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) { // Counting sort
            arr[index] = i + minVal;
            index++;
            count[i]--;
        }
    }

    delete[] count;
}

int main() {
    int arr[] = {62, 31, 84, 96, 19, 47, 31, 19, 62};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    distributionCountingSort(arr, n);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
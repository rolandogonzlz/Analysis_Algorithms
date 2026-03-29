//Merge Sort algorithm
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;


//struct for to prove the stability of merge sort

struct Item {
    int key;          
    string label;     // string label to differentiate items with the same key
};

// View the vector<int>
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

// View the vector<Item>
void printItems(const vector<Item>& v) {
    for (const auto& item : v) {
        cout << "(" << item.key << ", " << item.label << ") ";
    }
    cout << endl;
}

// =====================================================
// MERGE SORT for integers
// =====================================================
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {   // <= help to make it stable, if they are equal, we take the one from the left first
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// =====================================================
// MERGE SORT for Items (to prove stability)
// =====================================================
void mergeItems(vector<Item>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Item> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        // only compare the keys, not the labels
        // If they are equal, we take the one from the left first
        // This makes the implementation stable
        if (L[i].key <= R[j].key) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortItems(vector<Item>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortItems(arr, left, mid);
        mergeSortItems(arr, mid + 1, right);
        mergeItems(arr, left, mid, right);
    }
}

// =====================================================
// QUICK SORT
// =====================================================
int partitionQS(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // pivote = last element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// =====================================================
// RANDOM VECTOR GENERATION
// =====================================================
vector<int> randomVector(int n, int minVal = 0, int maxVal = 100000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = dist(gen);
    }
    return v;
}

// =====================================================
// TIME MEASUREMENT
// =====================================================
double measureQuickSortTime(vector<int> arr) {
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, (int)arr.size() - 1);
    auto end = high_resolution_clock::now();

    duration<double, milli> elapsed = end - start;
    return elapsed.count(); // milisegundos
}

double averageQuickSortRandomTime(int n, int repetitions = 5) {
    double total = 0.0;
    for (int i = 0; i < repetitions; i++) {
        vector<int> arr = randomVector(n);
        total += measureQuickSortTime(arr);
    }
    return total / repetitions;
}

double worstCaseQuickSortTime(int n) {
    // list already sorted in ascending order, with pivot as last element, is the worst case for quicksort
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i;
    return measureQuickSortTime(arr);
}

// =====================================================
// MAIN
// =====================================================
int main() {
    cout << "======================================" << endl;
    cout << "PUNTO 2: MERGE SORT" << endl;
    cout << "======================================" << endl;

    vector<int> mergeExample = {38, 27, 43, 3, 9, 82, 10};
    cout << "Original List: ";
    printVector(mergeExample);

    mergeSort(mergeExample, 0, (int)mergeExample.size() - 1);

    cout << "Sorted List with Merge Sort: ";
    printVector(mergeExample);

    cout << endl;

    cout << "======================================" << endl;
    cout << "PUNTO 3: STABILITY OF MERGE SORT" << endl;
    cout << "======================================" << endl;

    vector<Item> items = {
        {2, "A"},
        {1, "B"},
        {2, "C"},
        {1, "D"},
        {2, "E"}
    };

    cout << "Original List: ";
    printItems(items);

    mergeSortItems(items, 0, (int)items.size() - 1);

    cout << "Sorted List by key: ";
    printItems(items);

    cout << "\nInterpretation:" << endl;
    cout << "The elements with key = 1 remain as B, D" << endl;
    cout << "The elements with key = 2 remain as A, C, E" << endl;
    cout << "The relative order of elements with equal keys is preserved." << endl;
    cout << "Conclusion: this implementation of Merge Sort IS stable." << endl;

    cout << endl;

    cout << "======================================" << endl;
    cout << "PUNTO 4: QUICK SORT WITH RANDOM LISTS" << endl;
    cout << "======================================" << endl;

    vector<int> quickExample = randomVector(15, 1, 100);
    cout << "Original List: ";
    printVector(quickExample);

    vector<int> quickSorted = quickExample;
    quickSort(quickSorted, 0, (int)quickSorted.size() - 1);

    cout << "Sorted List with Quick Sort: ";
    printVector(quickSorted);

    vector<int> control = quickExample;
    sort(control.begin(), control.end());

    cout << "Sorted List with std::sort: ";
    printVector(control);

    if (quickSorted == control) {
        cout << "Verification: Quick Sort sorted correctly." << endl;
    } else {
        cout << "Verification: ERROR in Quick Sort." << endl;
    }

    cout << endl;

    cout << "======================================" << endl;
    cout << "PUNTO 5: EMPIRICAL ANALYSIS OF QUICK SORT" << endl;
    cout << "======================================" << endl;

    vector<int> sizesRandom = {100, 500, 1000, 2000, 5000, 10000};

    cout << fixed << setprecision(6);
    cout << "\nApproximate average case (random lists):" << endl;
    cout << "n\tTimes(ms)\tTimes/(n log2 n)" << endl;

    for (int n : sizesRandom) {
        double t = averageQuickSortRandomTime(n, 5);
        double ratio = t / (n * log2((double)n));
        cout << n << "\t" << t << "\t\t" << ratio << endl;
    }

    cout << "\nApproximate worst case (already sorted lists):" << endl;
    cout << "n\tTimes(ms)\tTimes/(n^2)" << endl;

    vector<int> sizesWorst = {100, 500, 1000, 2000, 3000};

    for (int n : sizesWorst) {
        double t = worstCaseQuickSortTime(n);
        double ratio = t / ((double)n * n);
        cout << n << "\t" << t << "\t\t" << ratio << endl;
    }

    cout << "\nInterpretation:" << endl;
    cout << "- In random lists, Quick Sort usually performs close to O(n log n)." << endl;
    cout << "- In already sorted lists with the last element as pivot, it can approach O(n^2)." << endl;
    cout << "- Therefore, the empirical analysis aligns with the mathematical analysis." << endl;

    return 0;
}
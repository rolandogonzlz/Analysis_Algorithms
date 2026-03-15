/* Create a program that implements the Insertion Sort Algorithm. Your program has to be able to 
sort a randomly generated array of alphabetic characters. Decide if you have to do or not any 
adjustments for the algorithm to work with alphabetic characters instead of integer numbers */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// function for print the array
void printArray(const std::vector<char>& arr){ // this line defines a function named printArray that takes a constant reference to a vector of char as  it parameter. the function does not return any value (void).
    for (char c : arr) { // this line starts a range-based for loop that iterates through each character c in the vector arr.
        std::cout << c << " "; // this line prints the current character c followed by a space to the standard output.
    }
    std::cout << std::endl; // this line prints a newline character to the standard output after the loop has finished printing all characters.
}

// function for insertion sort
void insertionSort(std::vector<char>& arr){ 
    int n = arr.size(); // this line declares an int variable n and initializes it with the size of the vector arr using the size() member function.

    for (int i =1; i < n; i++){
        char key = arr[i]; // this line declares a char variable key and initializes it with the value of the current element at index i in the vector arr.
        int j = i -1; // this line declares an int variable j and initializes it with the value of i minus 1, which represents the index of the last sorted element in the vector.

        while (j >= 0 && arr[j] > key) { // this line starts a while loop that continues as long as j is greater than or equal to 0 and the character at index j in the vector arr is greater than the key character. 
            //This condition ensures that we are still within the bounds of the sorted portion of the array and that we need to shift elements to make room for the key.
            arr[j + 1] = arr[j]; // this line shifts the character at index j in the vector arr to the right by assigning it to the position at index j + 1.
            j--;
        }
        arr[j + 1] = key; // this line places the key character in its correct position in the sorted portion of the array by assigning it to the position at index j + 1, which is the first position after the last shifted element.
    }
}

int main(){
    srand(time(0)); // this line seeds the random number generator with the current time using the srand() function, which ensures that the sequence of random numbers generated will be different each time the program is run.

    int n;
    std::cout << "Enter the number of characters to sort: "; // this line prompts the user to enter the number of characters they want to sort by printing a message to the standard output.
    std::cin >> n; // this line reads an integer value from the standard input and stores it in the variable n.

    std::vector<char> arr(n); // this line declares a vector of char named arr with a size of n, which will be used to store the randomly generated characters.

    // Generate random alphabetic characters of A to Z
    for (int i=0; i<n; i++){
        arr[i] = 'A' + rand() % 26; // this line generates a random alphabetic character by adding a random number between 0 and 25 (inclusive) to the ASCII value of 'A'. The resulting character is stored in the vector arr at index i.
    }

    std::cout<<"\nOriginal array:\n "; 
    printArray(arr);

    insertionSort(arr);

    std::cout<<"\nSorted array:\n ";
    printArray(arr);

    return 0;
}
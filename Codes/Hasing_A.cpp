//Implement a hashing algorithm using C++ (no dictionaries or libraries allowed). Use closed
//hashing as the collision resolution method.

#include <iostream>

//This class implements a hashing algorithm
class HashTable {
private:
    int* table; // table[i] is the i-th element in the array
    int size;
    int emptyValue;

public: // Constructor to initialize the hash table
    HashTable(int tableSize) {
        size = tableSize;
        emptyValue = -1;
        table = new int[size]; //if the size is 10, then table[0] to table[9] are empty

        for (int i = 0; i < size; i++) {
            table[i] = emptyValue;
        }
    }

    // Destructor to free the memory used by the hash table
    ~HashTable() {
        delete[] table;
    }
// Hash function to calculate the index for a given key
    int hashFunction(int key) {
        return key % size;
    }
    // these Inserts a key-value pair into the hash table
    void insert(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index] != emptyValue) {
            index = (index + 1) % size;
            if (index == startIndex) {
                std::cout << "The hash table is full, the key cannot be inserted." << std::endl;
                return;
            }
        }

        table[index] = key;
        std::cout << "Element " << key << " inserted at position " << index << std::endl;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index] != emptyValue) {
            if (table[index] == key) {
                return true;
            }

            index = (index + 1) % size;
            if (index == startIndex) {
                break;
            }
        }

        return false;
    }

    void display() {
        std::cout << "\nTabla Hash:\n";
        for (int i = 0; i < size; i++) {
            std::cout << i << ": ";
            if (table[i] == emptyValue) {
                std::cout << "Empty";
            } else {
                std::cout << table[i];
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    HashTable ht(10);

    ht.insert(23);
    ht.insert(43);
    ht.insert(13);
    ht.insert(27);
    ht.insert(33);

    ht.display();

    int key = 43;
    if (ht.search(key)) {
        std::cout << "\nThe element " << key << " exists in the table." << std::endl;
    } else {
        std::cout << "\nThe element " << key << " does not exist in the table." << std::endl;
    }

    key = 50;
    if (ht.search(key)) {
        std::cout << "The element " << key << " exists in the table." << std::endl;
    } else {
        std::cout << "The element " << key << " does not exist in the table." << std::endl;
    }

    return 0;
}
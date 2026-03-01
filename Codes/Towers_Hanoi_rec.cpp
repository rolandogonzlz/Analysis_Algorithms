#include <iostream>
#include <chrono>

long long moveCount = 0;

void play(int disco, int tower1, int tower2, int tower3, bool printMoves) {
    if (disco == 0) return;

    if (disco == 1) {
        moveCount++;
        if (printMoves) {
            std::cout << "Move disk 1 from tower " << tower1
                      << " to tower " << tower3 << std::endl;
        }
    } else {
        play(disco - 1, tower1, tower3, tower2, printMoves);

        moveCount++;
        if (printMoves) {
            std::cout << "Move disk " << disco << " from tower " << tower1
                      << " to tower " << tower3 << std::endl;
        }

        play(disco - 1, tower2, tower1, tower3, printMoves);
    }
}

long long expectedMoves(int n) {
    return (1LL << n) - 1;  // 2^n - 1
}

int main() {
    std::cout << "Towers of Hanoi problem solved recursively.\n";

    int disco;
    std::cout << "Enter the number of disks: ";
    std::cin >> disco;

    if (disco <= 0) {
        std::cout << "Number of disks must be positive.\n";
        return 0;
    }

    bool printMoves = (disco <= 10); // ejemplo: imprime solo si n es pequeño
    // Para medir tiempos de verdad, ponlo en false:
    // bool printMoves = false;

    moveCount = 0;

    auto start = std::chrono::high_resolution_clock::now();
    play(disco, 1, 2, 3, printMoves);
    auto end = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\nExpected moves (2^n - 1): " << expectedMoves(disco) << "\n";
    std::cout << "Counted moves:            " << moveCount << "\n";
    std::cout << "Time (ms):                " << ms << "\n";

    return 0;
}

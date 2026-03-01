#include <iostream>
#include <stack>
#include <chrono>

long long moveCount = 0;

void moveOne(std::stack<int>& from, std::stack<int>& to,
             int fromId, int toId, bool printMoves) {
    int disk = from.top();
    from.pop();
    to.push(disk);

    moveCount++;

    if (printMoves) {
        std::cout << "Move disk " << disk
                  << " from tower " << fromId
                  << " to tower " << toId << "\n";
    }
}

void moveLegal(std::stack<int>& A, std::stack<int>& B,
               int AId, int BId, bool printMoves) {
    if (A.empty()) {
        moveOne(B, A, BId, AId, printMoves);
    } else if (B.empty()) {
        moveOne(A, B, AId, BId, printMoves);
    } else if (A.top() < B.top()) {
        moveOne(A, B, AId, BId, printMoves);
    } else {
        moveOne(B, A, BId, AId, printMoves);
    }
}

void hanoiIterative(int n, bool printMoves) {
    std::stack<int> t1, t2, t3;

    for (int i = n; i >= 1; --i) {
        t1.push(i);
    }

    long long total = (1LL << n) - 1; // 2^n - 1

    for (long long i = 1; i <= total; ++i) {
        if (n % 2 == 1) {
            // impar: (1<->3), (1<->2), (2<->3)
            if (i % 3 == 1) moveLegal(t1, t3, 1, 3, printMoves);
            else if (i % 3 == 2) moveLegal(t1, t2, 1, 2, printMoves);
            else moveLegal(t2, t3, 2, 3, printMoves);
        } else {
            // par: (1<->2), (1<->3), (2<->3)
            if (i % 3 == 1) moveLegal(t1, t2, 1, 2, printMoves);
            else if (i % 3 == 2) moveLegal(t1, t3, 1, 3, printMoves);
            else moveLegal(t2, t3, 2, 3, printMoves);
        }
    }
}

long long expectedMoves(int n) {
    return (1LL << n) - 1;
}

int main() {
    int disco;
    std::cout << "Enter the number of disks: ";
    std::cin >> disco;

    if (disco <= 0) {
        std::cout << "Number of disks must be positive.\n";
        return 0;
    }

    // Para medir tiempo REAL: pon false
    // Para ver movimientos con n pequeño: true
    bool printMoves = (disco <= 10);

    moveCount = 0;

    auto start = std::chrono::high_resolution_clock::now();
    hanoiIterative(disco, printMoves);
    auto end = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\nExpected moves (2^n - 1): " << expectedMoves(disco) << "\n";
    std::cout << "Counted moves:            " << moveCount << "\n";
    std::cout << "Time (ms):                " << ms << "\n";

    return 0;
}
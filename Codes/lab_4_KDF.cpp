#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip> // for std::setw 

//Part 1: knapsack problem 0/1

void knapsack_exhaustive(int n){
    std::vector<int> weigth(n);
    std::vector<int> value(n);

    for (int i=0; i < n; i++){
        weigth[i] = std::rand() % 10 + 1; // random weight between 1 and 10
        value[i] = std::rand() % 20 + 1; // random value between 1 and 20

    }
    int capacity = n * 5; // capacity is 5 times the number of items

    int max_value = 0;
    int max_weight = 0;
    std::vector<int> best_selection(n, 0);

    auto start = std::chrono::high_resolution_clock::now(); // Start time measurement

    for (int mask = 0; mask < (1 << n); mask++) { // Iterate through all subsets
        int weight_total = 0;
        int value_total = 0;
        std::vector<int> seleccion(n, 0);   // Vector to track selected items

        for (int i = 0; i < n; i++) {       // Check if the i-th item is included in the current subset
            if (mask & (1 << i)) {
                weight_total += weigth[i];
                value_total += value[i];
                seleccion[i] = 1;           // Mark item as selected
            }
        }

        if (weight_total <= capacity && value_total > max_value) { // Update best solution if current subset is valid and has a better value
            max_value = value_total;
            max_weight = weight_total;
            best_selection = seleccion;
        }
        
    }
    auto fin = std::chrono::high_resolution_clock::now();       // End time measurement
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - start); // Calculate duration in milliseconds

    std::cout << "\n===== KNAPSACK 0/1 =====\n";
    std::cout << "Number of items: " << n << "\n";
    std::cout << "Knapsack capacity: " << capacity << "\n";

    std::cout << "\nGenerated items:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Item " << i
                  << " -> Weight: " << weigth[i]
                  << ", Value: " << value[i] << "\n";
    }

    std::cout << "\nBest value found: " << max_value << "\n";
    std::cout << "Total weight of the best solution: " << max_weight << "\n";

    std::cout << "Selected items: ";
    for (int i = 0; i < n; i++) {
        if (best_selection[i] == 1) {
            std::cout << i << " ";
        }
    }
    std::cout << "\nExecution time: " << duracion.count() << " ms\n";
}

void tabla_tiempos_knapsack() {
    std::cout << "===== TABLE OF KNAPSACK TIMES =====\n";

    for (int n = 4; n <= 20; n++) { // Test for n from 4 to 20
        std::vector<int> pesos(n);
        std::vector<int> valores(n);

        for (int i = 0; i < n; i++) {   // Generate random weights and values for the items
            pesos[i] = std::rand() % 10 + 1;
            valores[i] = std::rand() % 20 + 1;
        }

        int capacidad = n * 5;
        int mejor_valor = 0;

        auto inicio = std::chrono::high_resolution_clock::now();    // Start time measurement

        for (int mask = 0; mask < (1 << n); mask++) {   // Iterate through all subsets
            int peso_total = 0;
            int valor_total = 0;

            for (int i = 0; i < n; i++) {   // Check if the i-th item is included in the current subset
                if (mask & (1 << i)) {
                    peso_total += pesos[i];
                    valor_total += valores[i];
                }
            }

            if (peso_total <= capacidad && valor_total > mejor_valor) { // Update best value if current subset is valid and has a better value
                mejor_valor = valor_total;
            }
        }

        auto fin = std::chrono::high_resolution_clock::now();   // End time measurement
        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

        std::cout << "n = " << std::setw(2) << n
                  << " -> " << duracion.count() << " ms\n";
    }
}

// -----------------------------
// PART 2: DFS
// -----------------------------
// Recursive DFS function and its execution function
void dfs_recursivo(int nodo, const std::vector<std::vector<int>>& grafo, std::vector<bool>& visitado) {// Mark the current node as visited and print it
    visitado[nodo] = true; // Mark the current node as visited
    std::cout << nodo << " ";   // Print the current node

    for (int vecino : grafo[nodo]) {    // Iterate through the neighbors of the current node
        if (!visitado[vecino]) {    // If the neighbor has not been visited, recursively call DFS on it
            dfs_recursivo(vecino, grafo, visitado); // Recursive call for the neighbor
        }
    }
}

void ejecutar_dfs() {
    std::vector<std::vector<int>> grafo = {// Adjacency list representation of the graph
        {1, 2},     // 0
        {0, 3, 4},  // 1
        {0, 5},     // 2
        {1},        // 3
        {1, 5},     // 4
        {2, 4}      // 5
    };

    std::vector<bool> visitado(grafo.size(), false); // Vector to keep track of visited nodes

    std::cout << "\n===== DFS =====\n";         // Print header for DFS section
    std::cout << "Recorrido DFS desde el nodo 0: "; // Start DFS from node 0
    dfs_recursivo(0, grafo, visitado);  // Start DFS from node 0
    std::cout << "\n";
}

// -----------------------------
// PART 3: BFS
// -----------------------------
void bfs(int inicio, const std::vector<std::vector<int>>& grafo) { // Vector to keep track of visited nodes and a queue for BFS
    std::vector<bool> visitado(grafo.size(), false);    // Vector to keep track of visited nodes
    std::queue<int> cola;   // Queue for BFS

    visitado[inicio] = true;        // Mark the starting node as visited and enqueue it
    cola.push(inicio);              // Enqueue the starting node

    while (!cola.empty()) {         // While the queue is not empty, process nodes
        int nodo = cola.front();    // Get the front node from the queue and remove it
        cola.pop();                // Print the current node

        std::cout << nodo << " ";   // Iterate through the neighbors of the current node

        for (int vecino : grafo[nodo]) {    // If the neighbor has not been visited, mark it as visited and enqueue it
            if (!visitado[vecino]) {        // Mark the neighbor as visited and enqueue it
                visitado[vecino] = true;    // Mark the neighbor as visited
                cola.push(vecino);          // Enqueue the neighbor
            }
        }
    }
}

void ejecutar_bfs() {
    std::vector<std::vector<int>> grafo = { // Adjacency list representation of the graph
        {1, 2},     // 0
        {0, 3, 4},  // 1
        {0, 5},     // 2
        {1},        // 3
        {1, 5},     // 4
        {2, 4}      // 5
    };

    std::cout << "\n===== BFS =====\n";
    std::cout << "Recorrido BFS desde el nodo 0: ";     
    bfs(0, grafo);
    std::cout << "\n";
}

// -----------------------------
// MAIN
// -----------------------------

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator with the current time

    tabla_tiempos_knapsack();
    knapsack_exhaustive(5);

    ejecutar_dfs();
    ejecutar_bfs();

    return 0;


}
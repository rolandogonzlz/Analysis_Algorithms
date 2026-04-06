// Implement the forward elimination step of Gaussian elimination
#include <iostream>
#include <vector>
#include <iomanip> // for std::setprecision

//this function prints the augmented matrix in a readable format
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for(std::size_t i = 0; i < matrix.size(); ++i) {
        for(std::size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << std::fixed << std::setprecision(2) 
            << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// This function performs the forward elimination step of Gaussian elimination
bool forwardElimination(std::vector<std::vector<double> >& augmentedMatrix) {
    int n = static_cast<int>(augmentedMatrix.size());

    for (int k = 0; k < n - 1; ++k) {
        if (augmentedMatrix[k][k] == 0.0) {
            std::cout << "Error: zero pivot encountered at row " << k << std::endl;
            return false;
        }

        for (int i = k + 1; i < n; ++i) {
            double factor = augmentedMatrix[i][k] / augmentedMatrix[k][k];

            for (int j = k; j <= n; ++j) {
                augmentedMatrix[i][j] = augmentedMatrix[i][j] - factor * augmentedMatrix[k][j];
            }
        }
    }

    return true;
}

int main() {
    std::vector<std::vector<double> > augmentedMatrix = {
        {2, 1, -1, 8},
        {-3, -1, 2, -11},
        {-2, 1, 2, -3}
    };

    std::cout << "Original augmented matrix [A|b]:" << std::endl;
    printMatrix(augmentedMatrix);

    bool success = forwardElimination(augmentedMatrix);

    if (success) {
        std::cout << std::endl;
        std::cout << "Upper triangular matrix after forward elimination:" << std::endl;
        printMatrix(augmentedMatrix);
    }

    return 0;
}
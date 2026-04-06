//Implement an algorithm that can solve a system of equations using LU decomposition. LU 
//decomposition has to be based on Gaussian Elimination
#include <iostream>
#include <vector>
#include <iomanip>


//this function prints the elements of a matrix in a readable format
void imprimirMatriz(std::vector<std::vector<double> > M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            std::cout << std::setw(10) << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//this function prints the elements of a vector in a readable format
void imprimirVector(std::vector<double> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
    std::cout << std::endl;
}

//this function performs LU decomposition on a given matrix A, resulting in a lower triangular matrix L and an upper triangular matrix U. The function uses Gaussian elimination to achieve this decomposition, where the upper triangular matrix U is formed by performing row operations on the original matrix A, and the lower triangular matrix L is constructed to keep track of the factors used in these row operations.
void descomposicionLU(std::vector<std::vector<double> > A,
                      std::vector<std::vector<double> >& L,
                      std::vector<std::vector<double> >& U) {
    int n = A.size();

    U = A;
    L.assign(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1;
    }

    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            double factor = U[i][k] / U[k][k];
            L[i][k] = factor;

            for (int j = k; j < n; j++) {
                U[i][j] = U[i][j] - factor * U[k][j];
            }
        }
    }
}


//this function performs forward substitution to solve Ly = b, where L is a lower triangular matrix and b is a vector of constants. The function returns the solution vector y, which contains the values of the intermediate variables that satisfy the equation Ly = b.
std::vector<double> sustitucionHaciaAdelante(std::vector<std::vector<double> > L, std::vector<double> b) {
    int n = L.size();
    std::vector<double> y(n);

    for (int i = 0; i < n; i++) {
        double suma = 0;

        for (int j = 0; j < i; j++) {
            suma = suma + L[i][j] * y[j];
        }

        y[i] = (b[i] - suma) / L[i][i];
    }

    return y;
}

//this function performs backward substitution to solve Ux = y, where U is an upper triangular matrix and y is a vector of constants. The function returns the solution vector x, which contains the values of the unknown variables that satisfy the equation Ux = y.
std::vector<double> sustitucionHaciaAtras(std::vector<std::vector<double> > U, std::vector<double> y) {
    int n = U.size();
    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        double suma = 0;

        for (int j = i + 1; j < n; j++) {
            suma = suma + U[i][j] * x[j];
        }

        x[i] = (y[i] - suma) / U[i][i];
    }

    return x;
}

int main() {
    std::vector<std::vector<double> > A = {
        {2, -1, 1},
        {3, 3, 9},
        {3, 3, 5}
    };

    std::vector<double> b = {8, 0, -6};

    std::vector<std::vector<double> > L;
    std::vector<std::vector<double> > U;

    descomposicionLU(A, L, U);

    std::vector<double> y = sustitucionHaciaAdelante(L, b);
    std::vector<double> x = sustitucionHaciaAtras(U, y);

    std::cout << "Matriz L:" << std::endl;
    imprimirMatriz(L);

    std::cout << "Matriz U:" << std::endl;
    imprimirMatriz(U);

    std::cout << "Vector y:" << std::endl;
    imprimirVector(y);

    std::cout << "Solucion final x:" << std::endl;
    imprimirVector(x);

    return 0;
}

//Design the backwards substitution algorithm and show that it is running time is in O(n^2) 

// if we have an upper triangular matrix U and a vector y,
// we can solve for the unknown vector x in the equation Ux = y using backwards substitution. The algorithm starts from the last row of the matrix and works its way upwards, solving for each variable in turn.
#include <iostream>
#include <vector>


//this function prints the augmented matrix in a readable format
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for(std::size_t i = 0; i < matrix.size(); ++i) {
        for(std::size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// this function performs the backwards substitution algorithm to solve Ux = b, where U is an upper triangular matrix and b is a vector of constants. The function returns the solution vector x.
std::vector<double> backwardSustitution(std::vector<std::vector<double>> U, std::vector<double> b){
    int n = U.size();
    std::vector<double> x(n);

    for(int i = n-1; i >=0; i--){
        double suma = 0;

        for (int j = i+1; j < n; j++)
        {
            suma += U[i][j] * x[j]; // this line calculates the sum of the products of the known variables and their corresponding coefficients in the upper triangular matrix.
        }
        x[i] = (b[i] - suma) / U[i][i]; 
// this line calculates the value of the unknown variable x[i] by subtracting the sum from the corresponding constant b[i] and dividing by the coefficient U[i][i] of the variable in the upper triangular matrix.
    }
    return x;

}

int main(){
    std::vector<std::vector<double>> U = {
        {2, 1, -1},
        {0, -5, 1},
        {0, 0, 3}
    };

    std::vector<double> b = {8, -11, -3};

//the original equation is Ux = b, where U is the upper triangular matrix and b is the vector of constants. The goal is to solve for the unknown vector x using backwards substitution.
    std::cout << "The original equation is: " << std::endl;
    printMatrix(U);
    std::cout << "b: " << std::endl;
    printMatrix({b});


    std::vector<double> x = backwardSustitution(U, b);

    std::cout << "The solution is: " << std::endl;
    for (int i = 0; i< x.size(); i++){ // this loop prints the solution vector x, which contains the values of the unknown variables that satisfy the equation Ux = b.
        std::cout << "x[" << i << "] = " << x[i] << std::endl; // this line prints the value of each variable in the solution vector x, along with its index for clarity.
        
    }
    

    return 0;
}
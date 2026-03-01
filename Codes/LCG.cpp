#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <fstream> 

// LCG: Linear Congruential Generator
// x_{n+1} = (a * x_n + c) mod m
// Parameters:
struct LCG {
    uint64_t a, c, m;
    uint64_t x;

    LCG(uint64_t seed, uint64_t a_, uint64_t c_, uint64_t m_)
        : a(a_), c(c_), m(m_), x(seed) {}

    uint64_t nextInt() {
        x = (a * x + c) % m; // Update state
        return x;
    }

    double next01() {
        return (double)nextInt() / (double)m; // [0,1)
    }
};

int main() {
    // Parámetros fáciles (m no muy grande para evitar problemas)
    uint64_t m = 2147483647ULL;   // 2^31 - 1
    uint64_t a = 48271ULL;        // Park-Miller
    uint64_t c = 0ULL;              // c=0 para multiplicativo
    uint64_t seed = 123456ULL;      // Semilla inicial

    LCG rng(seed, a, c, m);

    const int N = 200000;           //number of random numbers to generate
    const int BINS = 20;            // Number of bins for histogram
    std::vector<long long> hist(BINS, 0);   // Histogram bins

    long double sum = 0.0L;
    long double sumsq = 0.0L;

    for (int i = 0; i < N; ++i) {       // Generate a random number in [0,1)
        double u = rng.next01();
        sum += u;
        sumsq += (long double)u * u;        // For variance calculation

        int b = (int)(u * BINS);            // Determine which bin it falls into
        if (b == BINS) b = BINS - 1;        // Handle the edge case where u is exactly 1.0 (though it shouldn't happen)
        hist[b]++;
    }

    long double mean = sum / N;         // Calculate mean
    long double var = (sumsq / N) - mean * mean;    // Calculate variance

    std::cout << "LCG test\n";
    std::cout << "N=" << N << "\n";
    std::cout << "Mean = " << (double)mean << " (ideal uniform: 0.5)\n";
    std::cout << "Var  = " << (double)var  << " (ideal uniform: 1/12 ~ 0.08333)\n\n";

    std::cout << "Histogram (" << BINS << " bins)\n";       // Print histogram
    for (int i = 0; i < BINS; ++i) {
        double left = (double)i / BINS;
        double right = (double)(i + 1) / BINS;

        std::cout << std::fixed << std::setprecision(2)
                  << "[" << left << "," << right << "): "
                  << hist[i] << "\n";
    }

    //save histogram to file
    std::ofstream out("hist.csv");
    out << "bin_left,bin_right,count\n";
    for (int i = 0; i < BINS; ++i) {
        double left = (double)i / BINS;
        double right = (double)(i + 1) / BINS;
        out << left << "," << right << "," << hist[i] << "\n";
    }
    out.close();

    std::cout << "\nSaved histogram to hist.csv (open in Excel and insert a chart).\n";

    return 0;
}
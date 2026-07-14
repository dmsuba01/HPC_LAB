#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "ijk.hpp"
#include "ikj.hpp"
#include "jik.hpp"
#include "jki.hpp"
#include "kij.hpp"
#include "kji.hpp"

// ---------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------

// Default matrix size. Can be overridden with a command-line argument,
// e.g. "./MatrixMultiplication 200" for a quick smaller-scale test run.
const int DEFAULT_N = 2500;

const int MIN_VALUE = 0;
const int MAX_VALUE = 99;

// ---------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------

// Generates an n x n matrix (flattened, row-major) of random integers.
std::vector<int> generateRandomMatrix(int n, unsigned int seed) {
    std::vector<int> matrix(static_cast<size_t>(n) * n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(MIN_VALUE, MAX_VALUE);

    for (auto& value : matrix) {
        value = dist(rng);
    }
    return matrix;
}

// Measures how long a matrix-multiply function takes, in milliseconds.
template <typename MatMulFunc>
long long measureTime(MatMulFunc func, const std::vector<int>& A,
                       const std::vector<int>& B, std::vector<int>& C, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    func(A, B, C, n);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Holds the timing result for one loop-order variant.
struct OrderResult {
    std::string name;
    long long timeMs;
};

// ---------------------------------------------------------------------
// main
// ---------------------------------------------------------------------

int main(int argc, char* argv[]) {
    int n = DEFAULT_N;
    if (argc > 1) {
        n = std::atoi(argv[1]);
        if (n <= 0) {
            std::cerr << "Invalid matrix size provided, using default: " << DEFAULT_N << "\n";
            n = DEFAULT_N;
        }
    }

    std::cout << "Matrix size: " << n << " x " << n << "\n";
    std::cout << "Generating random matrices...\n";

    std::vector<int> A = generateRandomMatrix(n, 1);
    std::vector<int> B = generateRandomMatrix(n, 2);

    std::vector<int> C_ijk(static_cast<size_t>(n) * n);
    std::vector<int> C_ikj(static_cast<size_t>(n) * n);
    std::vector<int> C_jik(static_cast<size_t>(n) * n);
    std::vector<int> C_jki(static_cast<size_t>(n) * n);
    std::vector<int> C_kij(static_cast<size_t>(n) * n);
    std::vector<int> C_kji(static_cast<size_t>(n) * n);

    std::vector<OrderResult> results;

    std::cout << "Running ijk...\n";
    results.push_back({"ijk", measureTime(matMulIJK, A, B, C_ijk, n)});

    std::cout << "Running ikj...\n";
    results.push_back({"ikj", measureTime(matMulIKJ, A, B, C_ikj, n)});

    std::cout << "Running jik...\n";
    results.push_back({"jik", measureTime(matMulJIK, A, B, C_jik, n)});

    std::cout << "Running jki...\n";
    results.push_back({"jki", measureTime(matMulJKI, A, B, C_jki, n)});

    std::cout << "Running kij...\n";
    results.push_back({"kij", measureTime(matMulKIJ, A, B, C_kij, n)});

    std::cout << "Running kji...\n";
    results.push_back({"kji", measureTime(matMulKJI, A, B, C_kji, n)});

    // All six orders compute the exact same sums in the exact same
    // accumulation order, so their results must match element-for-element.
    bool allMatch = (C_ijk == C_ikj) && (C_ikj == C_jik) && (C_jik == C_jki) &&
                     (C_jki == C_kij) && (C_kij == C_kji);

    // Find the fastest order.
    OrderResult fastest = results[0];
    for (const auto& r : results) {
        if (r.timeMs < fastest.timeMs) {
            fastest = r;
        }
    }

    // ---------------------------------------------------------------
    // Write report
    // ---------------------------------------------------------------
    std::ofstream report("../output/comparison_report.txt");
    if (!report.is_open()) {
        std::cerr << "Error: could not open output file.\n";
        return 1;
    }

    report << "===================================================\n";
    report << "     MATRIX MULTIPLICATION LOOP ORDER COMPARISON\n";
    report << "===================================================\n\n";
    report << "Matrix Size : " << n << " x " << n << "\n\n";

    for (const auto& r : results) {
        report << "Loop Order " << r.name << " : " << r.timeMs << " milliseconds\n";
    }

    report << "\n---------------------------------------------------\n\n";
    report << "Fastest Loop Order\n\n";
    report << fastest.name << " (" << fastest.timeMs << " milliseconds)\n\n";
    report << "Correctness Check : " << (allMatch ? "PASSED" : "FAILED") << "\n\n";

    report << "Observations\n\n";
    report << "* ikj and kij tend to be fastest: both A and B are swept\n";
    report << "  row-wise (cache-friendly) in the innermost loop.\n";
    report << "* jki and kji tend to be slowest: at least one matrix is\n";
    report << "  accessed column-wise, causing frequent cache misses.\n";
    report << "* ijk and jik fall in between, with A accessed row-wise\n";
    report << "  but B accessed column-wise in the innermost loop.\n";
    report << "===================================================\n";

    report.close();

    // ---------------------------------------------------------------
    // Console summary
    // ---------------------------------------------------------------
    std::cout << "\nAll six variants complete. Results written to output/comparison_report.txt\n";
    std::cout << "Correctness check: " << (allMatch ? "PASSED" : "FAILED") << "\n";
    std::cout << "Fastest: " << fastest.name << " (" << fastest.timeMs << " ms)\n";

    return 0;
}
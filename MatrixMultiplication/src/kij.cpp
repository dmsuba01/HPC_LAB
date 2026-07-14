#include "kij.hpp"

void matMulKIJ(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n) {
    std::fill(C.begin(), C.end(), 0);

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            int aik = A[i * n + k];
            for (int j = 0; j < n; ++j) {
                C[i * n + j] += aik * B[k * n + j];
            }
        }
    }
}
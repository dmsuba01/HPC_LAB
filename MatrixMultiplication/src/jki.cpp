#include "jki.hpp"

void matMulJKI(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n) {
    std::fill(C.begin(), C.end(), 0);

    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            int bkj = B[k * n + j];
            for (int i = 0; i < n; ++i) {
                C[i * n + j] += A[i * n + k] * bkj;
            }
        }
    }
}
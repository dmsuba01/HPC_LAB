#include "ikj.hpp"

void matMulIKJ(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n) {
    // C must be zero-initialized since we accumulate into it directly.
    std::fill(C.begin(), C.end(), 0);

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            int aik = A[i * n + k];
            for (int j = 0; j < n; ++j) {
                C[i * n + j] += aik * B[k * n + j];
            }
        }
    }
}
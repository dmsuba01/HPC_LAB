#ifndef MATMUL_JIK_H
#define MATMUL_JIK_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// j -> i -> k loop order.
void matMulJIK(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_JIK_H
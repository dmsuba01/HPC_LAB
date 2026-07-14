#ifndef MATMUL_JKI_H
#define MATMUL_JKI_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// j -> k -> i loop order.
void matMulJKI(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_JKI_H
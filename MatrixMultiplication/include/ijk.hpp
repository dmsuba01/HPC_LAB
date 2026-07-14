#ifndef MATMUL_IJK_H
#define MATMUL_IJK_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// i -> j -> k loop order: C[i][j] = sum_k A[i][k] * B[k][j]
void matMulIJK(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_IJK_H
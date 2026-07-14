#ifndef MATMUL_KJI_H
#define MATMUL_KJI_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// k -> j -> i loop order.
void matMulKJI(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_KJI_H
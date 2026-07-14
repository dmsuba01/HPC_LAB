#ifndef MATMUL_KIJ_H
#define MATMUL_KIJ_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// k -> i -> j loop order.
void matMulKIJ(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_KIJ_H
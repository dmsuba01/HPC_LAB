#ifndef MATMUL_IKJ_H
#define MATMUL_IKJ_H

#include <vector>

// Multiplies two N x N matrices (stored row-major, flattened) using the
// i -> k -> j loop order.
void matMulIKJ(const std::vector<int>& A, const std::vector<int>& B,
               std::vector<int>& C, int n);

#endif // MATMUL_IKJ_H
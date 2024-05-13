// 
// Recursive Gemm example
// 

#include <tlapack/plugins/legacyArray.hpp>
#include <tlapack/blas/gemm.hpp>
#include <tlapack/lapack/lange.hpp>

#include <vector>
#include <iostream>
#include <iomanip>

using namespace tlapack;

template<typename A_t, typename B_t, typename C_t>
void gemm_recursive( A_t& A, B_t& B, C_t& C ){
    // Let's just assume all matrices have the same type
    using T = type_t<A_t>;
    using idx_t = size_type<A_t>;

    idx_t m = nrows(A);
    idx_t k = ncols(A);
    idx_t n = ncols(B);

    tlapack_check(nrows(B) == k);
    tlapack_check(nrows(C) == m);
    tlapack_check(ncols(C) == n);

    // Implement gemm_recursive here
    for (idx_t i = 0; i < m; i++)
        for (idx_t j = 0; j < n; j++)
            for (idx_t l = 0; l < k; l++)
                C(i, j) += A(i, l) * B(l, j);

}

int main()
{
    using T = double;
    using idx_t = size_t;

    idx_t m = 10;
    idx_t n = 10;
    idx_t k = 10;

    // Create a matrix and vector
    // Note: these are all managed as objects
    // no need to deallocate them manually
    std::vector<T> A_(m * k);
    tlapack::LegacyMatrix<T, idx_t> A(m, k, A_.data(), m);

    std::vector<T> B_(k * n);
    tlapack::LegacyMatrix<T, idx_t> B(k, n, B_.data(), k);

    std::vector<T> C_(m * n);
    tlapack::LegacyMatrix<T, idx_t> C(m, n, C_.data(), m);

    // Initialize the matrices
    for (idx_t i = 0; i < m; i++)
        for (idx_t j = 0; j < k; j++)
            A(i, j) = rand() % 100;

    for (idx_t i = 0; i < k; i++)
        for (idx_t j = 0; j < n; j++)
            B(i, j) = rand() % 100;

    for (idx_t i = 0; i < m; i++)
        for (idx_t j = 0; j < n; j++)
            C(i, j) = 0.;

    // Call gemm_recursive
    gemm_recursive(A, B, C);


    // Calculate C = C - A*B (i.e. check the result of gemm_recursive)
    gemm(Op::NoTrans, Op::NoTrans, 1.0, A, B, -1.0, C);

    auto error_norm = lange(Norm::Fro, C);

    std::cout << "Error norm: " << error_norm << std::endl;

    return 0;
}
// 
// A minor modification of the lu example to use mpreal instead of double
// Notice how only two lines of code were changed to use mpreal instead of double
// 

#include <tlapack/plugins/legacyArray.hpp>
#include <tlapack/plugins/mpreal.hpp>
#include <tlapack/lapack/getrf.hpp>
#include <tlapack/lapack/lu_mult.hpp>

#include <vector>
#include <iostream>
#include <iomanip>



int main()
{
    using T = mpfr::mpreal;
    using idx_t = size_t;

    idx_t n = 10;

    // Create a matrix and vector
    // Note: these are all managed as objects
    // no need to deallocate them manually
    std::vector<T> A_(n * n);
    tlapack::LegacyMatrix<T, idx_t> A(n, n, A_.data(), n);
    std::vector<idx_t> ipiv(n);

    // Initialize the matrix
    for (idx_t i = 0; i < n; i++)
    {
        for (idx_t j = 0; j < n; j++)
        {
            A(i, j) = rand() % 100;
        }
    }

    std::cout << "Matrix A:" << std::endl;
    for (idx_t i = 0; i < n; i++)
    {
        for (idx_t j = 0; j < n; j++)
        {
            std::cout << std::setw(9) << A(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Perform LU factorization
    int info = tlapack::getrf(A, ipiv);

    std::cout << "Info:" << info << std::endl;

    std::cout << "Matrix L:" << std::endl;
    for (idx_t i = 0; i < n; i++)
    {
        for (idx_t j = 0; j < n; j++)
        {
            if (i > j)
            {
                std::cout << std::setw(9) << A(i, j) << " ";
            }
            else if (i == j)
            {
                std::cout << std::setw(9) << 1 << " ";
            }
            else
            {
                std::cout << std::setw(9) << 0 << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix U:" << std::endl;
    for (idx_t i = 0; i < n; i++)
    {
        for (idx_t j = 0; j < n; j++)
        {
            if (i <= j)
            {
                std::cout << std::setw(9) << A(i, j) << " ";
            }
            else
            {
                std::cout << std::setw(9) << 0 << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Pivot vector:" << std::endl;
    for (idx_t i = 0; i < n; i++)
    {
        std::cout << ipiv[i] << " ";
    }
    std::cout << std::endl;

    tlapack::lu_mult(A);
    for (idx_t j = n - 1; j != idx_t(-1); j--)
    {
        auto vect1 = tlapack::row(A, j);
        auto vect2 = tlapack::row(A, ipiv[j]);
        tlapack::swap(vect1, vect2);
    }

    std::cout << "inv(P) * L*U:" << std::endl;
    for (idx_t i = 0; i < n; i++)
    {
        for (idx_t j = 0; j < n; j++)
        {
            std::cout << std::setw(9) << A(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
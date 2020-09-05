// Name: rotateMatrix.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/04/2020-12:01:05
// Description: Rotate an MxN matrix 90 degrees and print the result

#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

template<std::size_t N, std::size_t M>
constexpr std::array<std::array<int, M>, N> rotateMatrix(std::array<std::array<int, N>, M>& A)
{
    std::array<std::array<int, M>, N> A_prime {};

    for (std::size_t i {}; i < M; ++i)
        for (std::size_t j {}; j < N; ++j)
            A_prime[j][M - std::floor(i + N/2)] = A[i][j];

    return A_prime;
}

template<std::size_t N, std::size_t M>
constexpr void printMatrices(const std::array<std::array<int, N>, M>& A, const std::array<std::array<int, M>, N>& A_prime)
{
    std::cout << "A\tA'" << std::endl;

    for (std::size_t i {}, j {}; i < N || j < M; ++i, ++j)
    {
        for (std::size_t k {}; k < N; ++k)
        {
            if (i >= M) break;
            std::cout << A[i][k] << " ";
        }

        std::cout << "\t";

        for (std::size_t k {}; k < M; ++k)
        {
            if (j >= N) break;
            std::cout << A_prime[j][k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::array<std::array<int, 2>, 2> A2x2 { { { {1, 2} },
                                               { {3, 4} } } };

    std::array<std::array<int, 3>, 2> A2x3 { { { {1, 2, 3} },
                                               { {4, 5, 6} } } };

    std::array<std::array<int, 2>, 3> A3x2 { { { {1, 2} },
                                               { {3, 4} },
                                               { {5, 6} } } };

    std::array<std::array<int, 3>, 3> A3x3 { { { {1, 2, 3} },
                                               { {4, 5, 6} },
                                               { {7, 8, 9} } } };

    auto A2x2_prime = rotateMatrix(A2x2);
    auto A2x3_prime = rotateMatrix(A2x3);
    auto A3x2_prime = rotateMatrix(A3x2);
    auto A3x3_prime = rotateMatrix(A3x3);

    printMatrices(A2x2, A2x2_prime);
    printMatrices(A2x3, A2x3_prime);
    printMatrices(A3x2, A3x2_prime);
    printMatrices(A3x3, A3x3_prime);
}
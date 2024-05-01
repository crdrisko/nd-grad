// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: squareMatrix.cpp
// Author: crdrisko
// Date: 10/14/2023-07:51:15
// Description:

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>

namespace ND_Research
{
    template<std::size_t N, typename = std::enable_if_t<(N >= 1UL)>>
    struct SquareMatrix
    {
    private:
        double arr[N][N] {};

    public:
        constexpr SquareMatrix() = default;

        template<typename... Types, typename = std::enable_if_t<(sizeof...(Types) == (N * N))>>
        explicit constexpr SquareMatrix(Types... elems) : arr {elems...}
        {
            static_assert((std::is_same_v<Types, double> && ...));
        }

        constexpr SquareMatrix<N - 1> cofactor(int i, int j) const
        {
            std::size_t countRow {};

            SquareMatrix<N - 1> ret {};

            for (std::size_t row {}; row < N; ++row)
            {
                std::size_t countCol {};

                if (row != i)
                {
                    for (std::size_t col {}; col < N; ++col)
                    {
                        if (col != j)
                        {
                            ret(countRow, countCol) = arr[row][col];
                            ++countCol;
                        }
                    }

                    ++countRow;
                }
            }

            return ret;
        }

        template<std::size_t N_ret, typename = std::enable_if_t<(N_ret < N)>>
        constexpr SquareMatrix<N_ret> lowerSubMatrix() const
        {
            std::size_t countRow {};

            SquareMatrix<N_ret> ret {};

            for (std::size_t row {N - N_ret}; row < N; ++row)
            {
                std::size_t countCol {};

                for (std::size_t col {N - N_ret}; col < N; ++col)
                {
                    ret(countRow, countCol) = arr[row][col];
                    ++countCol;
                }

                ++countRow;
            }

            return ret;
        }

        constexpr double& operator()(int i, int j) { return arr[i][j]; }
        constexpr const double& operator()(int i, int j) const { return arr[i][j]; }
    };

    template<std::size_t N>
    std::ostream& operator<<(std::ostream& stream, const SquareMatrix<N>& M)
    {
        for (std::size_t i {}; i < N; ++i)
        {
            for (std::size_t j {}; j < N; ++j)
                stream << M(i, j) << ' ';

            stream << '\n';
        }

        return stream;
    }

    namespace details
    {
        template<std::size_t N>
        struct DeterminantImpl
        {
            static constexpr auto result(const SquareMatrix<N>& M)
            {
                double ret {};

                int sign {1};

                for (std::size_t i {}; i < N; ++i)
                {
                    ret += sign * M(0, i) * DeterminantImpl<N - 1>::result(M.cofactor(0, i));

                    sign *= -1;
                }

                return ret;
            }
        };

        template<>
        struct DeterminantImpl<2>
        {
            static constexpr double result(const SquareMatrix<2>& M) { return M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0); }
        };
    }   // namespace details

    template<std::size_t N>
    constexpr double determinant(const SquareMatrix<N>& M) { return details::DeterminantImpl<N>::result(M); }

    namespace details
    {
        /*!
         * An aggregate structure that can be used as the return type of the \c polynomialLeastSquaresFitting<>()
         *  function template.
         *
         * Returns the coefficents according to the following equation...
         *
         * \note We hide the return type in the \c details namespace so the user is encouraged to use
         *       structured binding as the way to return from \c polynomialLeastSquaresFitting<>().
         */
        template<typename... Types>
        struct PolynomicalLeastSquaresResult
        {
            static_assert( ((std::is_default_constructible<Types>() && ...)) );

            std::tuple<Types...> coefficients;
        };
    }   // namespace details

    enum class Polynomials : std::size_t {Linear = 2, Quadratic, Cubic, Order4th, Order5th, Order6th, Order7th, Order8th, Order9th, Order10th};

    template<Polynomials Order, typename IteratorX, typename IteratorY = IteratorX,
        typename Tx = typename std::iterator_traits<IteratorX>::value_type,
        typename Ty = typename std::iterator_traits<IteratorY>::value_type,
        typename = std::enable_if_t<std::conjunction_v<std::is_default_constructible<Tx>, std::is_default_constructible<Ty>>>>
    constexpr decltype(auto) polynomialLeastSquaresFitting(IteratorX x_begin, IteratorX x_end, IteratorY y_begin, IteratorY y_end)
    {
        const std::ptrdiff_t x_size {x_end - x_begin}, y_size {y_end - y_begin};

        // if (x_size != y_size)
        //     throw InputSizeMismatch {"Common-Utilities", __FILE__, __LINE__};

        details::PolynomicalLeastSquaresResult<double, double, double, double, double, double, double, double, double, double, double> results {};

        double n = static_cast<double>(x_size);

        double x1 {};
        double x2 {};
        double x3 {};
        double x4 {};
        double x5 {};
        double x6 {};
        double x7 {};
        double x8 {};
        double x9 {};
        double x10 {};
        double x11 {};
        double x12 {};
        double x13 {};
        double x14 {};
        double x15 {};
        double x16 {};
        double x17 {};
        double x18 {};
        double x19 {};
        double x20 {};

        double y1 {};

        double x1y1 {};
        double x2y1 {};
        double x3y1 {};
        double x4y1 {};
        double x5y1 {};
        double x6y1 {};
        double x7y1 {};
        double x8y1 {};
        double x9y1 {};
        double x10y1 {};

        IteratorX x_iter = x_begin;
        IteratorY y_iter = y_begin;

        while (x_iter != x_end)
        {
            const double x_i = (*x_iter);
            const double y_i = (*y_iter);

            switch (Order)
            {
            case Polynomials::Order10th:
                x20 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x19 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x10y1 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order9th:
                x18 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x17 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x9y1 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order8th:
                x16 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x15 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x8y1 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order7th:
                x14 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x13 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x7y1 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order6th:
                x12 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x11 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x6y1 += x_i * x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order5th:
                x10 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x9 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x5y1 += x_i * x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Order4th:
                x8 += x_i * x_i * x_i * x_i * x_i * x_i * x_i * x_i;
                x7 += x_i * x_i * x_i * x_i * x_i * x_i * x_i;

                x4y1 += x_i * x_i * x_i * x_i * y_i;
            case Polynomials::Cubic:
                x6 += x_i * x_i * x_i * x_i * x_i * x_i;
                x5 += x_i * x_i * x_i * x_i * x_i;

                x3y1 += x_i * x_i * x_i * y_i;
            case Polynomials::Quadratic:
                x4 += x_i * x_i * x_i * x_i;
                x3 += x_i * x_i * x_i;

                x2y1 += x_i * x_i * y_i;
            case Polynomials::Linear:
                x2 += x_i * x_i;
                x1 += x_i;

                x1y1 += x_i * y_i;
                break;
            }

            y1 += y_i;

            ++x_iter;
            ++y_iter;
        }

        SquareMatrix<11> denominator {x20, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10,
                                      x19, x18, x17, x16, x15, x14, x13, x12, x11, x10, x9,
                                      x18, x17, x16, x15, x14, x13, x12, x11, x10, x9,  x8,
                                      x17, x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x7,
                                      x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,
                                      x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,
                                      x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,
                                      x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,
                                      x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,
                                      x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,
                                      x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a10 {x10y1, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10,
                              x9y1,  x18, x17, x16, x15, x14, x13, x12, x11, x10, x9,
                              x8y1,  x17, x16, x15, x14, x13, x12, x11, x10, x9,  x8,
                              x7y1,  x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x7,
                              x6y1,  x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,
                              x5y1,  x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,
                              x4y1,  x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,
                              x3y1,  x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,
                              x2y1,  x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,
                              x1y1,  x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,
                              y1,    x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a9 {x20, x10y1, x18, x17, x16, x15, x14, x13, x12, x11, x10,
                             x19, x9y1,  x17, x16, x15, x14, x13, x12, x11, x10, x9,
                             x18, x8y1,  x16, x15, x14, x13, x12, x11, x10, x9,  x8,
                             x17, x7y1,  x15, x14, x13, x12, x11, x10, x9,  x8,  x7,
                             x16, x6y1,  x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,
                             x15, x5y1,  x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,
                             x14, x4y1,  x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,
                             x13, x3y1,  x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,
                             x12, x2y1,  x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,
                             x11, x1y1,  x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,
                             x10, y1,    x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a8 {x20, x19, x10y1, x17, x16, x15, x14, x13, x12, x11, x10,
                             x19, x18, x9y1,  x16, x15, x14, x13, x12, x11, x10, x9,
                             x18, x17, x8y1,  x15, x14, x13, x12, x11, x10, x9,  x8,
                             x17, x16, x7y1,  x14, x13, x12, x11, x10, x9,  x8,  x7,
                             x16, x15, x6y1,  x13, x12, x11, x10, x9,  x8,  x7,  x6,
                             x15, x14, x5y1,  x12, x11, x10, x9,  x8,  x7,  x6,  x5,
                             x14, x13, x4y1,  x11, x10, x9,  x8,  x7,  x6,  x5,  x4,
                             x13, x12, x3y1,  x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,
                             x12, x11, x2y1,  x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,
                             x11, x10, x1y1,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,
                             x10, x9,  y1,    x7,  x6,  x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a7 {x20, x19, x18, x10y1, x16, x15, x14, x13, x12, x11, x10,
                             x19, x18, x17, x9y1,  x15, x14, x13, x12, x11, x10, x9,
                             x18, x17, x16, x8y1,  x14, x13, x12, x11, x10, x9,  x8,
                             x17, x16, x15, x7y1,  x13, x12, x11, x10, x9,  x8,  x7,
                             x16, x15, x14, x6y1,  x12, x11, x10, x9,  x8,  x7,  x6,
                             x15, x14, x13, x5y1,  x11, x10, x9,  x8,  x7,  x6,  x5,
                             x14, x13, x12, x4y1,  x10, x9,  x8,  x7,  x6,  x5,  x4,
                             x13, x12, x11, x3y1,  x9,  x8,  x7,  x6,  x5,  x4,  x3,
                             x12, x11, x10, x2y1,  x8,  x7,  x6,  x5,  x4,  x3,  x2,
                             x11, x10, x9,  x1y1,  x7,  x6,  x5,  x4,  x3,  x2,  x1,
                             x10, x9,  x8,  y1,    x6,  x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a6 {x20, x19, x18, x17, x10y1, x15, x14, x13, x12, x11, x10,
                             x19, x18, x17, x16, x9y1,  x14, x13, x12, x11, x10, x9,
                             x18, x17, x16, x15, x8y1,  x13, x12, x11, x10, x9,  x8,
                             x17, x16, x15, x14, x7y1,  x12, x11, x10, x9,  x8,  x7,
                             x16, x15, x14, x13, x6y1,  x11, x10, x9,  x8,  x7,  x6,
                             x15, x14, x13, x12, x5y1,  x10, x9,  x8,  x7,  x6,  x5,
                             x14, x13, x12, x11, x4y1,  x9,  x8,  x7,  x6,  x5,  x4,
                             x13, x12, x11, x10, x3y1,  x8,  x7,  x6,  x5,  x4,  x3,
                             x12, x11, x10, x9,  x2y1,  x7,  x6,  x5,  x4,  x3,  x2,
                             x11, x10, x9,  x8,  x1y1,  x6,  x5,  x4,  x3,  x2,  x1,
                             x10, x9,  x8,  x7,  y1,    x5,  x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a5 {x20, x19, x18, x17, x16, x10y1, x14, x13, x12, x11, x10,
                             x19, x18, x17, x16, x15, x9y1,  x13, x12, x11, x10, x9,
                             x18, x17, x16, x15, x14, x8y1,  x12, x11, x10, x9,  x8,
                             x17, x16, x15, x14, x13, x7y1,  x11, x10, x9,  x8,  x7,
                             x16, x15, x14, x13, x12, x6y1,  x10, x9,  x8,  x7,  x6,
                             x15, x14, x13, x12, x11, x5y1,  x9,  x8,  x7,  x6,  x5,
                             x14, x13, x12, x11, x10, x4y1,  x8,  x7,  x6,  x5,  x4,
                             x13, x12, x11, x10, x9,  x3y1,  x7,  x6,  x5,  x4,  x3,
                             x12, x11, x10, x9,  x8,  x2y1,  x6,  x5,  x4,  x3,  x2,
                             x11, x10, x9,  x8,  x7,  x1y1,  x5,  x4,  x3,  x2,  x1,
                             x10, x9,  x8,  x7,  x6,  y1,    x4,  x3,  x2,  x1,  n};

        SquareMatrix<11> a4 {x20, x19, x18, x17, x16, x15, x10y1, x13, x12, x11, x10,
                             x19, x18, x17, x16, x15, x14, x9y1,  x12, x11, x10, x9,
                             x18, x17, x16, x15, x14, x13, x8y1,  x11, x10, x9,  x8,
                             x17, x16, x15, x14, x13, x12, x7y1,  x10, x9,  x8,  x7,
                             x16, x15, x14, x13, x12, x11, x6y1,  x9,  x8,  x7,  x6,
                             x15, x14, x13, x12, x11, x10, x5y1,  x8,  x7,  x6,  x5,
                             x14, x13, x12, x11, x10, x9,  x4y1,  x7,  x6,  x5,  x4,
                             x13, x12, x11, x10, x9,  x8,  x3y1,  x6,  x5,  x4,  x3,
                             x12, x11, x10, x9,  x8,  x7,  x2y1,  x5,  x4,  x3,  x2,
                             x11, x10, x9,  x8,  x7,  x6,  x1y1,  x4,  x3,  x2,  x1,
                             x10, x9,  x8,  x7,  x6,  x5,  y1,    x3,   x2,  x1,  n};

        SquareMatrix<11> a3 {x20, x19, x18, x17, x16, x15, x14, x10y1, x12, x11, x10,
                             x19, x18, x17, x16, x15, x14, x13, x9y1,  x11, x10, x9,
                             x18, x17, x16, x15, x14, x13, x12, x8y1,  x10, x9,  x8,
                             x17, x16, x15, x14, x13, x12, x11, x7y1,  x9,  x8,  x7,
                             x16, x15, x14, x13, x12, x11, x10, x6y1,  x8,  x7,  x6,
                             x15, x14, x13, x12, x11, x10, x9,  x5y1,  x7,  x6,  x5,
                             x14, x13, x12, x11, x10, x9,  x8,  x4y1,  x6,  x5,  x4,
                             x13, x12, x11, x10, x9,  x8,  x7,  x3y1,  x5,  x4,  x3,
                             x12, x11, x10, x9,  x8,  x7,  x6,  x2y1,  x4,  x3,  x2,
                             x11, x10, x9,  x8,  x7,  x6,  x5,  x1y1,  x3,  x2,  x1,
                             x10, x9,  x8,  x7,  x6,  x5,  x4,  y1,    x2,  x1,  n};

        SquareMatrix<11> a2 {x20, x19, x18, x17, x16, x15, x14, x13, x10y1, x11, x10,
                             x19, x18, x17, x16, x15, x14, x13, x12, x9y1,  x10, x9,
                             x18, x17, x16, x15, x14, x13, x12, x11, x8y1,  x9,  x8,
                             x17, x16, x15, x14, x13, x12, x11, x10, x7y1,  x8,  x7,
                             x16, x15, x14, x13, x12, x11, x10, x9,  x6y1,  x7,  x6,
                             x15, x14, x13, x12, x11, x10, x9,  x8,  x5y1,  x6,  x5,
                             x14, x13, x12, x11, x10, x9,  x8,  x7,  x4y1,  x5,  x4,
                             x13, x12, x11, x10, x9,  x8,  x7,  x6,  x3y1,  x4,  x3,
                             x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x2y1,  x3,  x2,
                             x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x1y1,  x2,  x1,
                             x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  y1,    x1,  n};

        SquareMatrix<11> a1 {x20, x19, x18, x17, x16, x15, x14, x13, x12, x10y1, x10,
                             x19, x18, x17, x16, x15, x14, x13, x12, x11, x9y1,  x9,
                             x18, x17, x16, x15, x14, x13, x12, x11, x10, x8y1,  x8,
                             x17, x16, x15, x14, x13, x12, x11, x10, x9,  x7y1,  x7,
                             x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x6y1,  x6,
                             x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x5y1,  x5,
                             x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x4y1,  x4,
                             x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x3y1,  x3,
                             x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x2y1,  x2,
                             x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x1y1,  x1,
                             x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  y1,    n};

        SquareMatrix<11> a0 {x20, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10y1,
                             x19, x18, x17, x16, x15, x14, x13, x12, x11, x10, x9y1,
                             x18, x17, x16, x15, x14, x13, x12, x11, x10, x9,  x8y1,
                             x17, x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x7y1,
                             x16, x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x6y1,
                             x15, x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5y1,
                             x14, x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4y1,
                             x13, x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3y1,
                             x12, x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2y1,
                             x11, x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1y1,
                             x10, x9,  x8,  x7,  x6,  x5,  x4,  x3,  x2,  x1,  y1};

        double detDenom = (Order == Polynomials::Order10th) ? determinant(denominator)
                                                            : determinant(denominator.lowerSubMatrix<static_cast<std::size_t>(Order)>());

        switch (Order)
        {
        case Polynomials::Order10th:
            std::get<0>(results.coefficients)  = determinant(a0) / detDenom;
            std::get<1>(results.coefficients)  = determinant(a1) / detDenom;
            std::get<2>(results.coefficients)  = determinant(a2) / detDenom;
            std::get<3>(results.coefficients)  = determinant(a3) / detDenom;
            std::get<4>(results.coefficients)  = determinant(a4) / detDenom;
            std::get<5>(results.coefficients)  = determinant(a5) / detDenom;
            std::get<6>(results.coefficients)  = determinant(a6) / detDenom;
            std::get<7>(results.coefficients)  = determinant(a7) / detDenom;
            std::get<8>(results.coefficients)  = determinant(a8) / detDenom;
            std::get<9>(results.coefficients)  = determinant(a9) / detDenom;
            std::get<10>(results.coefficients) = determinant(a10) / detDenom;
            break;

        case Polynomials::Order9th:
            std::get<9>(results.coefficients) = determinant(a9.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Order8th:
            std::get<8>(results.coefficients) = determinant(a8.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Order7th:
            std::get<7>(results.coefficients) = determinant(a7.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Order6th:
            std::get<6>(results.coefficients) = determinant(a6.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Order5th:
            std::get<5>(results.coefficients) = determinant(a5.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Order4th:
            std::get<4>(results.coefficients) = determinant(a4.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Cubic:
            std::get<3>(results.coefficients) = determinant(a3.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Quadratic:
            std::get<2>(results.coefficients) = determinant(a2.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
        case Polynomials::Linear:
            std::get<1>(results.coefficients) = determinant(a1.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
            std::get<0>(results.coefficients) = determinant(a0.lowerSubMatrix<static_cast<std::size_t>(Order)>()) / detDenom;
            break;
        }

        return results;
    }
}   // namespace ND_Research

int main()
{
    const std::vector<double> x {0.0, 1.0, 2.0, 3.0, 4.0};
    const std::vector<double> y {2.0, 1.0, 0.0, 1.0, 2.0};

    auto [coefficients] = ND_Research::polynomialLeastSquaresFitting<ND_Research::Polynomials::Quadratic>(x.begin(), x.end(), y.begin(), y.end());

    auto [a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10] = coefficients;

    std::cout << "y = " << a0 << " + " << a1 << " x + " << a2 << " x^2 + " << a3 << " x^3\n";
}

#include <cstddef>
#include <iostream>

struct Vector3D
{
    double x, y, z;

    Vector3D() = default;

    Vector3D(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    double& operator[](int i) { return ((&x)[i]); }
    const double& operator[](int i) const { return ((&x)[i]); }
};

struct Matrix2D
{
private:
    double n[2][2];

public:
    Matrix2D() = default;

    Matrix2D(double n00, double n01, double n10, double n11)
    {
        n[0][0] = n00;
        n[0][1] = n10;
        n[1][0] = n01;
        n[1][1] = n11;
    }

    double& operator()(int i, int j) { return (n[j][i]); }
    const double& operator()(int i, int j) const { return (n[j][i]); }
};

struct Matrix3D
{
private:
    double n[3][3];

public:
    Matrix3D() = default;

    Matrix3D(double n00, double n01, double n02, double n10, double n11, double n12, double n20, double n21, double n22)
    {
        n[0][0] = n00;
        n[0][1] = n10;
        n[0][2] = n20;
        n[1][0] = n01;
        n[1][1] = n11;
        n[1][2] = n21;
        n[2][0] = n02;
        n[2][1] = n12;
        n[2][2] = n22;
    }

    Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
    {
        n[0][0] = a.x;
        n[0][1] = a.y;
        n[0][2] = a.z;
        n[1][0] = b.x;
        n[1][1] = b.y;
        n[1][2] = b.z;
        n[2][0] = c.x;
        n[2][1] = c.y;
        n[2][2] = c.z;
    }

    double& operator()(int i, int j) { return (n[j][i]); }
    const double& operator()(int i, int j) const { return (n[j][i]); }

    Matrix2D subMatrix(int i, int j) const
    {
        std::size_t countRow {};

        Matrix2D ret {};
        for (std::size_t row {}; row < 3; ++row)
        {
            std::size_t countCol {};

            if (row != i)
            {
                for (std::size_t col {}; col < 3; ++col)
                {
                    if (col != j)
                    {
                        ret(countRow, countCol) = n[col][row];
                        ++countCol;
                    }
                }

                ++countRow;
            }
        }

        return ret;
    }

    Vector3D& operator[](int j) { return (*reinterpret_cast<Vector3D*>(n[j])); }
    const Vector3D& operator[](int j) const { return (*reinterpret_cast<const Vector3D*>(n[j])); }
};

double determinant(const Matrix2D& M) { return M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0); }

double determinant(const Matrix3D& M)
{
    double ret {};

    int sign {1};

    for (std::size_t i {}; i < 3; ++i)
    {
        ret += sign * M(i, 0) * determinant(M.subMatrix(i, 0));

        sign *= -1;
    }

    return ret;
}

double determinant3D(const Matrix3D& M)
{
    return M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1)) - M(0, 1) * (M(1, 0) * M(2, 2) - M(1, 2) * M(2, 0))
           + M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0));
}

namespace details
{
    /*!
         * An aggregate structure that can be used as the return type of the \c quadraticLeastSquaresFitting<>()
         *  function template.
         * 
         * Returns the coefficents according to the following equation: ax^2 + bx + c.
         *
         * \note We hide the return type in the \c details namespace so the user is encouraged to use
         *       structured binding as the way to return from \c quadraticLeastSquaresFitting<>().
         */
    template<typename T_a,
        typename T_b = T_a,
        typename T_c = T_a,
        typename     = std::enable_if_t<std::conjunction_v<std::is_default_constructible<T_a>,
            std::is_default_constructible<T_b>,
            std::is_default_constructible<T_c>>>>
    struct QuadraticLeastSquaresResult
    {
        T_a a {};
        T_b b {};
        T_c c {};
    };
}   // namespace details

template<typename IteratorX,
    typename IteratorY = IteratorX,
    typename Tx        = typename std::iterator_traits<IteratorX>::value_type,
    typename Ty        = typename std::iterator_traits<IteratorY>::value_type,
    typename = std::enable_if_t<std::conjunction_v<std::is_default_constructible<Tx>, std::is_default_constructible<Ty>>>>
constexpr decltype(auto) quadraticLeastSquaresFitting(IteratorX x_begin, IteratorX x_end, IteratorY y_begin, IteratorY y_end)
{
    const std::ptrdiff_t x_size {x_end - x_begin}, y_size {y_end - y_begin};

    // if (x_size != y_size)
    //     throw InputSizeMismatch {"Common-Utilities", __FILE__, __LINE__};

    details::QuadraticLeastSquaresResult<double, double, double> results {};

    double n = static_cast<double>(x_size);

    double x1 {};
    double x2 {};
    double x3 {};
    double x4 {};

    double y1 {};

    double x1y1 {};
    double x2y1 {};

    IteratorX x_iter = x_begin;
    IteratorY y_iter = y_begin;

    while (x_iter != x_end)
    {
        const double x_i = (*x_iter);
        const double y_i = (*y_iter);

        x1 += x_i;
        x2 += x_i * x_i;
        x3 += x_i * x_i * x_i;
        x4 += x_i * x_i * x_i * x_i;

        y1 += y_i;

        x1y1 += x_i * y_i;
        x2y1 += x_i * x_i * y_i;

        ++x_iter;
        ++y_iter;
    }

    Matrix3D a_numerator {x2y1, x3, x2, x1y1, x2, x1, y1, x1, n};
    Matrix3D b_numerator {x4, x2y1, x2, x3, x1y1, x1, x2, y1, n};
    Matrix3D c_numerator {x4, x3, x2y1, x3, x2, x1y1, x2, x1, y1};

    Matrix3D denominator {x4, x3, x2, x3, x2, x1, x2, x1, n};

    double detDenom = determinant(denominator);

    // auto denominator = x4 * (x2 * x_size - x1 * x1) - x3 * (x3 * x_size - x1 * x2) + x2 * (x3 * x1 - x2 * x2);

    // auto a_numerator = x2y1 * (x2 * x_size - x1 * x1) - x3 * (x1y1 * x_size - x1 * y1) + x2 * (x1y1 * x1 - x2 * y1);
    // auto b_numerator = x4 * (x1y1 * x_size - x1 * y1) - x2y1 * (x3 * x_size - x1 * x2) + x2 * (x3 * y1 - x1y1 * x2);
    // auto c_numerator = x4 * (x2 * y1 - x1y1 * x1 ) - x3 * (x3 * y1 - x1y1 * x2) + x2y1 * (x3 * x1 - x2 * x2);

    results.a = determinant(a_numerator) / detDenom;
    results.b = determinant(b_numerator) / detDenom;
    results.c = determinant(c_numerator) / detDenom;

    return results;
}

int main()
{
    std::vector<double> x {0, 1, 2, 3, 4};
    std::vector<double> y {2, 1, 0, 1, 2};

    auto [a, b, c] = quadraticLeastSquaresFitting(x.begin(), x.end(), y.begin(), y.end());

    std::cout << "y = " << a << " x^2 + " << b << " x + " << c << "\n";

    Matrix3D mat {0, 1, 2, 3, 5, 5, 6, 7, 8};

    std::cout << std::boolalpha << (determinant3D(mat) == determinant(mat)) << '\n';

    // for (std::size_t row {}; row < 3; ++row)
    // {
    //     for (std::size_t col {}; col < 3; ++col)
    //     {
    //         Matrix2D temp = mat.subMatrix(row, col);

    //         std::cout << "Skip: " << row << ", " << col << ": " << temp(0, 0) << ' ' << temp(0, 1) << "\n            "
    //                   << temp(1, 0) << ' ' << temp(1, 1) << '\n';
    //     }
    // }
}

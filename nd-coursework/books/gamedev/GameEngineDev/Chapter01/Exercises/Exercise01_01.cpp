// Name: Exercise01_01.cpp
// Author: crdrisko
// Date: 08/22/2023-14:55:10
// Description: Interesting relations between the unit vectors i, j, k when represented as Vector3D

#include <iomanip>
#include <iostream>

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

std::ostream& operator<<(std::ostream& stream, const Vector3D& v)
{
    stream << "[" << std::setw(2) << v.x << "," << std::setw(2) << v.y << "," << std::setw(2) << v.z << " ]";
    return stream;
}

int main()
{
    const Vector3D i {1, 0, 0};
    const Vector3D j {0, 1, 0};
    const Vector3D k {0, 0, 1};

    // Part a)
    std::cout << "a) Dot(i, j) = " << Dot(i, j) << "\n   Dot(j, k) = " << Dot(j, k) << "\n   Dot(k, i) = " << Dot(k, i)
              << "\n\n";

    // Part b)
    std::cout << "b) Cross(i, j) = " << Cross(i, j) << "\n   Cross(j, i) = " << Cross(j, i)
              << "\n   Cross(j, k) = " << Cross(j, k) << "\n   Cross(k, j) = " << Cross(k, j)
              << "\n   Cross(k, i) = " << Cross(k, i) << "\n   Cross(i, k) = " << Cross(i, k) << "\n\n";

    // Part c)
    std::cout << "c) [i, j, k] = " << Dot(Cross(i, j), k) << "\n";
}

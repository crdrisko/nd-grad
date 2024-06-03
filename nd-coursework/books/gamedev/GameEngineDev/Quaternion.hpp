// Name: Quaternion.hpp
// Author: crdrisko
// Date: 06/03/2024-16:29:03
// Description: A culmination of all listings in chapter 2 pertaining to the Quaternion data structure

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

struct Quaternion
{
    float x, y, z, w;

    Quaternion() = default;
    Quaternion(float a, float b, float c, float s) : x {a}, y {b}, z {c}, w {s} {}
    Quaternion(const Vector3D& v, float s) : x {v.x}, y {v.y}, z {v.z}, w {s} {}

    const Vector3D& GetVectorPart() const { return (reinterpret_cast<const Vector3D&>(x)); }

    Matrix3D GetRotationMatrix();
    void SetRotationMatrix(const Matrix3D& m);
};

// clang-format off
Matrix3D Quaternion::GetRotationMatrix()
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    return (Matrix3D(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy),
                     2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx),
                     2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2)));
}

void Quaternion::SetRotationMatrix(const Matrix3D& m)
{
    float m00 = m(0, 0);
    float m11 = m(1, 1);
    float m22 = m(2, 2);

    float sum = m00 + m11 + m22;

    if (sum > 0.0f)
    {
        w = std::sqrt(sum + 1.0f) * 0.5f;
        float f = 0.25f / w;

        x = (m(2, 1) - m(1, 2)) * f;
        y = (m(0, 2) - m(2, 0)) * f;
        z = (m(1, 0) - m(0, 1)) * f;
    }
    else if (m00 > m11 && m00 > m22)
    {
        x = std::sqrt(m00 - m11 - m22 + 1.0f) * 0.5f;
        float f = 0.25f / x;

        y = (m(1, 0) + m(0, 1)) * f;
        z = (m(0, 2) + m(2, 0)) * f;
        w = (m(2, 1) - m(1, 2)) * f;
    }
    else if (m11 > m22)
    {
        y = std::sqrt(m11 - m00 - m22 + 1.0f) * 0.5f;
        float f = 0.25f / y;

        x = (m(1, 0) + m(0, 1)) * f;
        z = (m(2, 1) + m(1, 2)) * f;
        w = (m(0, 2) - m(2, 0)) * f;
    }
    else
    {
        z = std::sqrt(m22 - m00 - m11 + 1.0f) * 0.5f;
        float f = 0.25f / z;

        x = (m(0, 2) + m(2, 0)) * f;
        y = (m(2, 1) + m(1, 2)) * f;
        w = (m(1, 0) - m(0, 1)) * f;
    }
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    return (Quaternion(
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z));
}
// clang-format on


#endif

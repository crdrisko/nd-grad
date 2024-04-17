#pragma once

class Vec2
{
public:
    float x {};
    float y {};

    Vec2() = default;
    Vec2(float xin, float yin);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;
    Vec2 operator/(const Vec2& rhs) const;

    void operator+=(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
    void operator*=(const Vec2& rhs);
    void operator/=(const Vec2& rhs);

    float distSquared(const Vec2& rhs) const;
};

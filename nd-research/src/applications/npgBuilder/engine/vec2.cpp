// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: vec2.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description: 

#include "npgBuilder/vec2.hpp"

Vec2::Vec2(float xin, float yin) : x {xin}, y {yin} {}

bool Vec2::operator==(const Vec2& rhs) const { return x == rhs.x && y == rhs.y; }

bool Vec2::operator!=(const Vec2& rhs) const { return !(*this == rhs); }

Vec2 Vec2::operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

Vec2 Vec2::operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }

Vec2 Vec2::operator*(const Vec2& rhs) const { return Vec2(x * rhs.x, y * rhs.y); }

Vec2 Vec2::operator/(const Vec2& rhs) const { return Vec2(x / rhs.x, y / rhs.y); }

void Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const Vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void Vec2::operator/=(const Vec2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

float Vec2::distSquared(const Vec2& rhs) const
{
    Vec2 diff = rhs - *this;

    return diff.x * diff.x + diff.y * diff.y;
}

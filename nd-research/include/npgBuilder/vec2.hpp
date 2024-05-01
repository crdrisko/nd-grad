// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: vec2.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description: 

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_VEC2_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_VEC2_HPP

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

#endif

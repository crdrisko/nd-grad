// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: components.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_COMPONENTS_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_COMPONENTS_HPP

#include <SFML/Graphics.hpp>

#include "npgBuilder/vec2.hpp"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 position {};
    std::string atomType {};

    CTransform() = default;
    CTransform(const Vec2& pos, const std::string& at) : position {pos}, atomType {at} {}
};

class CShape : public Component
{
public:
    sf::CircleShape circle;

    CShape() = default;

    CShape(float radius, const sf::Color& fill) : circle {radius}
    {
        circle.setFillColor(fill);
        circle.setOrigin(radius, radius);
    }
};

class CBonds : public Component
{
public:
    std::size_t maxBonds {3};
    std::size_t currentBonds {};

    CBonds() = default;
    explicit CBonds(std::size_t bonds) : maxBonds {bonds} {}
};

class CSelectable : public Component
{
public:
    bool selected {};

    CSelectable() = default;
};

#endif

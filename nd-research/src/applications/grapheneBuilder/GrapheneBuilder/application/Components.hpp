// Name: Components.hpp
// Author: crdrisko
// Date: 08/30/2023-06:52:58
// Description:

#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

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

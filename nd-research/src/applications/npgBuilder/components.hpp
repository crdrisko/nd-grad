// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: components.hpp
// Author: crdrisko
// Date: 11/13/2024-06:09:51
// Description:

#ifndef ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_COMPONENTS_HPP
#define ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include <dryphys/math.hpp>
#include <engine2d/components.hpp>

namespace NPGBuilder
{
    class CTransform : public Engine2D::Component
    {
    public:
        DryPhys::Vector3D position {};
        std::string atomType {};

        CTransform() = default;
        CTransform(const DryPhys::Vector3D& pos, const std::string& at) : position {pos}, atomType {at} {}
    };

    class CShape : public Engine2D::Component
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

    class CBonds : public Engine2D::Component
    {
    public:
        std::size_t maxBonds {3};
        std::size_t currentBonds {};

        CBonds() = default;
        explicit CBonds(std::size_t bonds) : maxBonds {bonds} {}
    };

    class CSelectable : public Engine2D::Component
    {
    public:
        bool selected {};

        CSelectable() = default;
    };
}   // namespace NPGBuilder
#endif

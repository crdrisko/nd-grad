// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: forwardDeclare.hpp
// Author: crdrisko
// Date: 11/13/2024-06:09:43
// Description:

#ifndef ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_FORWARDDECLARE_HPP
#define ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_FORWARDDECLARE_HPP

#include <memory>

#include <engine2d/entity.hpp>
#include <engine2d/entityManager.hpp>
#include <engine2d/entityMemoryPool.hpp>

namespace NPGBuilder
{
    class NPGScene;

    class CTransform;
    class CShape;
    class CBonds;
    class CSelectable;

    using ConcreteEntityManager = Engine2D::EntityManager<CTransform, CShape, CBonds, CSelectable>;
    using ConcreteEntityPtr     = std::shared_ptr<Engine2D::Entity<CTransform, CShape, CBonds, CSelectable>>;
}   // namespace NPGBuilder

#endif

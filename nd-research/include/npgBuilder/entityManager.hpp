// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: entityManager.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ENTITYMANAGER_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ENTITYMANAGER_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "npgBuilder/entity.hpp"

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager
{
private:
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;

    std::size_t m_totalEntities {};

    void removeDeadEntities(EntityVec& entities);

public:
    EntityManager() = default;

    void update();

    std::shared_ptr<Entity> addEntity(const std::string& tag);

    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};

#endif

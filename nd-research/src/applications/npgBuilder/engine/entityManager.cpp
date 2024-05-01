// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: entityManager.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description: 

#include "npgBuilder/entityManager.hpp"

#include <algorithm>
#include <memory>
#include <string>

void EntityManager::update()
{
    for (auto e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for (auto& [tag, entities] : m_entityMap)
    {
        removeDeadEntities(entities);
    }
}

void EntityManager::removeDeadEntities(EntityVec& entities)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](auto e) { return !(e->isActive()); }),
        entities.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(entity);

    return entity;
}

EntityVec& EntityManager::getEntities() { return m_entities; }

EntityVec& EntityManager::getEntities(const std::string& tag) { return m_entityMap[tag]; }

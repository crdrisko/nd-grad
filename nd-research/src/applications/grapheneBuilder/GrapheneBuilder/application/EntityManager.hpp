//
//

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Entity.hpp"

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

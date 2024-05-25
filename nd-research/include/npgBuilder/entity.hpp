// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: entity.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ENTITY_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ENTITY_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <tuple>

#include "npgBuilder/components.hpp"

using ComponentTuple = std::tuple<CTransform, CShape, CBonds, CSelectable>;

class Entity
{
private:
    friend class EntityManager;

    bool m_active     = true;
    std::size_t m_id  = 0;
    std::string m_tag = "default";
    ComponentTuple m_components;

    Entity(const std::size_t id, const std::string& tag) : m_id {id}, m_tag {tag} {}

public:
    void destroy() { m_active = false; }
    bool isActive() const { return m_active; }
    const std::string& tag() const { return m_tag; }

    std::size_t& id() { return m_id; }
    const std::size_t& id() const { return m_id; }

    template<typename T>
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component       = T(std::forward<TArgs>(mArgs)...);
        component.has   = true;
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    const T& getComponent() const
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};

#endif

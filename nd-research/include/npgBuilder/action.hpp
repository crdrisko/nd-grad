// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: action.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ACTION_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_NPGBUILDER_ACTION_HPP

#include <sstream>
#include <string>

#include "npgBuilder/vec2.hpp"

class Action
{
private:
    std::string m_name = "NONE";
    std::string m_type = "NONE";
    Vec2 m_pos         = Vec2(0, 0);

public:
    Action() = default;
    Action(const std::string& name, const std::string& type) : m_name {name}, m_type {type} {}
    Action(const std::string& name, const Vec2& mousePos) : m_name {name}, m_pos {mousePos} {}
    Action(const std::string& name, const std::string& type, const Vec2& mousePos)
        : m_name {name}, m_type {type}, m_pos {mousePos}
    {
    }

    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }
    const Vec2& pos() const { return m_pos; }

    std::string toString() const
    {
        std::stringstream ss;
        ss << m_name << " " << m_type << " " << static_cast<int>(m_pos.x) << " " << static_cast<int>(m_pos.y);
        return ss.str();
    }
};

#endif

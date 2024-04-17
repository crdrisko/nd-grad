//
//

#ifndef ACTION_HPP
#define ACTION_HPP

#include <sstream>
#include <string>

#include "Vec2.hpp"

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

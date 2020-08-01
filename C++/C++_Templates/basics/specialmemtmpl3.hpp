// Name: specialmemtmpl3.hpp - Version 1.0.0
// Author: cdrisko
// Date: 08/01/2020-08:45:56
// Description: Using std::enable_if<> to allow for COPY-CONSTR to be called by switching off TMPL-CONSTR

#ifndef SPECIALMEMTMPL3_HPP
#define SPECIALMEMTMPL3_HPP

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// C++11 Version:
// template<typename T>
// using EnableIfString
//     = typename std::enable_if<std::is_convertible<T, std::string>::value>::type;

// C++14 Version:
// template<typename T>
// using EnableIfString
//     = std::enable_if_t<std::is_convertible<T, std::string>::value>;

// C++17 Version:
template<typename T>
using EnableIfString
    = std::enable_if_t<std::is_convertible_v<T, std::string>>;

class Person
{
private:
    std::string name;

public:
    // generic constructor for passed initial name:
    template<typename STR, typename = EnableIfString<STR>>
    explicit Person(STR&& n) : name(std::forward<STR>(n))
    {
        std::cout << "TMPL-CONSTR for '" << name << "'\n";
    }

    // copy and move constructor:
    Person(Person const& p) : name(p.name)
    {
        std::cout << "COPY-CONSTR Person '" << name << "'\n";
    }

    Person(Person&& p) : name(std::move(p.name))
    {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};

#endif

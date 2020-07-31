// Name: boolstringgetbool.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:51:13
// Description: Full specialization for BoolString::getValue<>() for bool

#ifndef BOOLSTRINGGETBOOL_HPP
#define BOOLSTRINGGETBOOL_HPP

#include "boolstring.hpp"

template<>
inline bool BoolString::get<bool>() const
{
    return value == "true" || value == "1" || value == "on";
}

#endif

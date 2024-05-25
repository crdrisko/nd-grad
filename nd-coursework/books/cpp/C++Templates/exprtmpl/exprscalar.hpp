// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprscalar.hpp
// Author: crdrisko
// Date: 09/29/2020-07:21:51
// Description: Class for objects that represent scalars

#ifndef EXPRSCALAR_HPP
#define EXPRSCALAR_HPP

#include <cstddef>

template<typename T>
class A_Scalar
{
private:
    T const& s;   // value of the scalar

public:
    // constructor initializes value
    constexpr A_Scalar(T const& v) : s(v) {}

    // for index operations, the scalar is the value of each element
    constexpr T const& operator[](std::size_t) const { return s; }

    // scalars have zero as size
    constexpr std::size_t size() const { return 0; }
};

#endif

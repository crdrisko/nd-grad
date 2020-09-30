// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isdefaultconstructible1.hpp
// Author: crdrisko
// Date: 08/29/2020-08:29:52
// Description: A basic implementation of a trait to determine whether or not a type is default constructible using SFINAE

#ifndef ISDEFAULTCONSTRUCTIBLE1_HPP
#define ISDEFAULTCONSTRUCTIBLE1_HPP

#include "issame.hpp"

template<typename T>
struct IsDefaultConstructibleT
{
private:
    // test() trying to substitute call of a default constructor for T passed as U:
    template<typename U, typename = decltype(U())>
    static char test(void*);

    // test() fallback:
    template<typename>
    static long test(...);

public:
    static constexpr bool value = IsSameT<decltype(test<T>(nullptr)), char>::value;
};

#endif

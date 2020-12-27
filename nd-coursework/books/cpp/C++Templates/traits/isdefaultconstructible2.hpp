// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isdefaultconstructible2.hpp
// Author: crdrisko
// Date: 08/29/2020-09:13:21
// Description: Another implementation of a trait to determine whether or not a type is default constructible using SFINAE

#ifndef ISDEFAULTCONSTRUCTIBLE2_HPP
#define ISDEFAULTCONSTRUCTIBLE2_HPP

#include <type_traits>

template<typename T>
struct IsDefaultConstructibleHelper
{
private:
    // test() trying to substitute call of a default constructor for T passed as U:
    template<typename U, typename = decltype(U())>
    static std::true_type test(void*);

    // test() fallback:
    template<typename>
    static std::false_type test(...);

public:
    using Type = decltype(test<T>(nullptr));
};

template<typename T>
struct IsDefaultConstructibleT : IsDefaultConstructibleHelper<T>::Type {};

#endif

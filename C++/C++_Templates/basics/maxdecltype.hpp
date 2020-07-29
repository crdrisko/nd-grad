// Name: maxdecltype.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-21:06:12
// Description: Declaring the way in which the return type should be derived for our max() function (C++11 and on)

#ifndef MAXDECLTYPE_HPP
#define MAXDECLTYPE_HPP

template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(b<a?a:b)
{
    return b < a ? a : b;
}

#endif

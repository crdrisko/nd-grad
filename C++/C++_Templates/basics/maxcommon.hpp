// Name: maxcommon.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-21:15:42
// Description: How to choose the more general type to return for our max() function (C++14 and on)

#ifndef MAXCOMMON_HPP
#define MAXCOMMON_HPP

#include <type_traits>

template <typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif

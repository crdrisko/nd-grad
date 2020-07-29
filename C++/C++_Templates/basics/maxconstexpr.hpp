// Name: maxconstexpr.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-08:34:31
// Description: A version of the max() function that can be used at compile time

#ifndef MAXCONSTEXPR_HPP
#define MAXCONSTEXPR_HPP

template<typename T1, typename T2>
constexpr auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif

// Name: maxauto.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-21:03:18
// Description: Using auto to deduce the return type of our max() function (C++14 and on)

#ifndef MAXAUTO_HPP
#define MAXAUTO_HPP

template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif

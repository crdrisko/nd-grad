// Name: max1.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-20:34:40
// Description: A function template that returns the maximum of two values

#ifndef MAX1_HPP
#define MAX1_HPP

template <typename T>
T max(T a, T b)
{
    // if b < a then yield a else yield b
    return b < a ? a : b;
}

#endif

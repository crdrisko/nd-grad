// Name: addvalue.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-17:47:44
// Description: Defines a group of functions for which a certain value can be added

#ifndef ADDVALUE_HPP
#define ADDVALUE_HPP

template <int Val, typename T>
T addValue(T x)
{
    return x + Val;
}

#endif

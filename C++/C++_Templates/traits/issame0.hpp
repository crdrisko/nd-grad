// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: issame0.hpp
// Author: crdrisko
// Date: 08/28/2020-21:30:42
// Description: Determining if two types are equal

#ifndef ISSAME0_HPP
#define ISSAME0_HPP

template<typename T1, typename T2>
struct IsSameT
{
    static constexpr bool value = false;
};

template<typename T>
struct IsSameT<T, T>
{
    static constexpr bool value = true;
};


#endif

// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasbegin.hpp
// Author: crdrisko
// Date: 08/31/2020-08:02:41
// Description: Determining if a type has the begin() member function

#ifndef HASBEGIN_HPP
#define HASBEGIN_HPP

#include <type_traits>   // for true_type, false_type, and void_t
#include <utility>       // for declval

// primary template:
template<typename, typename = std::void_t<>>
struct HasBeginT : std::false_type
{
};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct HasBeginT<T, std::void_t<decltype(std::declval<T>().begin())>> : true_type
{
};

#endif

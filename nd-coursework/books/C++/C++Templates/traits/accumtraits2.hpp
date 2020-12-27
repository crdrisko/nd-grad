// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accumtraits2.hpp
// Author: crdrisko
// Date: 08/18/2020-07:42:34
// Description: Traits template for the accumulator function template

#ifndef ACCUMTRAITS2_HPP
#define ACCUMTRAITS2_HPP

template<typename T>
struct AccumulationTraits;

template<>
struct AccumulationTraits<char>
{
    using AccT = int;
};

template<>
struct AccumulationTraits<short>
{
    using AccT = int;
};

template<>
struct AccumulationTraits<int>
{
    using AccT = long;
};

template<>
struct AccumulationTraits<unsigned int>
{
    using AccT = unsigned long;
};

template<>
struct AccumulationTraits<float>
{
    using AccT = double;
};

#endif

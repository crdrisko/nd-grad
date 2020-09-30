// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accumtraits3.hpp
// Author: crdrisko
// Date: 08/18/2020-07:51:30
// Description: Using static member variables to define good zero values for various template parameter types

#ifndef ACCUMTRAITS3_HPP
#define ACCUMTRAITS3_HPP

template<typename T>
struct AccumulationTraits;

template<>
struct AccumulationTraits<char>
{
    using AccT = int;
    static AccT const zero = 0;
};

template<>
struct AccumulationTraits<short>
{
    using AccT = int;
    static AccT const zero = 0;
};

template<>
struct AccumulationTraits<int>
{
    using AccT = long;
    static AccT const zero = 0;
};

template<>
struct AccumulationTraits<unsigned int>
{
    using AccT = unsigned long;
    static AccT const zero = 0;
};

template<>
struct AccumulationTraits<float>
{
    using AccT = double;
    static AccT const zero = 0;
};

#endif

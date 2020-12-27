// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accumtraits4.hpp
// Author: crdrisko
// Date: 08/18/2020-07:58:15
// Description: Using static member function to define good zero values for various template parameter types

#ifndef ACCUMTRAITS4_HPP
#define ACCUMTRAITS4_HPP

template<typename T>
struct AccumulationTraits;

template<>
struct AccumulationTraits<char>
{
    using AccT = int;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccumulationTraits<short>
{
    using AccT = int;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccumulationTraits<int>
{
    using AccT = long;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccumulationTraits<unsigned int>
{
    using AccT = unsigned long;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccumulationTraits<float>
{
    using AccT = double;
    static constexpr AccT zero() { return 0; }
};

#endif

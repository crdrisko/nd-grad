// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accumtraits4bigint.hpp
// Author: crdrisko
// Date: 08/18/2020-07:58:26
// Description: Definition of a BigInt and it's corresponding AccumulationTraits template

#ifndef ACCUMTRAITS4BIGINT_HPP
#define ACCUMTRAITS4BIGINT_HPP

#include "accumtraits4.hpp"

class BigInt
{
private:
    long long value;

public:
    BigInt(long long Value) : value {Value} {}
    // ...
};


template<>
struct AccumulationTraits<BigInt>
{
    using AccT = BigInt;
    static BigInt const zero() { return BigInt {0}; }
};

#endif

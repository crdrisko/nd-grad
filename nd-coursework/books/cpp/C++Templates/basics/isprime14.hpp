// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isprime14.hpp
// Author: crdrisko
// Date: 08/12/2020-13:51:12
// Description: A C++14 version of the isPrime() functionality

#ifndef ISPRIME14_HPP
#define ISPRIME14_HPP

constexpr bool isPrime(unsigned int p)
{
    for (unsigned int d = 2; d <= p / 2; ++d)
        if (p % d == 0)
            return false;

    return p > 1;
}

#endif

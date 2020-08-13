// Name: isprime14.hpp - Version 1.0.0
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

// Name: isprime11.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-13:37:03
// Description: A C++11 version of the isPrime() functionality

#ifndef ISPRIME11_HPP
#define ISPRIME11_HPP

constexpr bool doIsPrime(unsigned p, unsigned d)            // p: number to check, d: current divisor
{
    return d != 2 ? (p % d != 0) && doIsPrime(p, d - 1)     // check this and smaller divisors
                  : (p % 2 != 0);                           // end recursion if divisor is 2
}

constexpr bool isPrime(unsigned p)
{
    return p < 4 ? !(p < 2)                                 // handle special cases
                 : doIsPrime(p, p / 2);                     // start with recursion with divisor from p / 2
}

#endif

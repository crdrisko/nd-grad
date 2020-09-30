// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sumpolicy1.hpp
// Author: crdrisko
// Date: 08/18/2020-10:05:00
// Description: A policy to be used with the accumulator template to add a sequence of numbers

#ifndef SUMPOLICY1_HPP
#define SUMPOLICY1_HPP

class SumPolicy
{
public:
    template<typename T1, typename T2>
    static void accumulate(T1& total, T2 const& value)
    {
        total += value;
    }
};

#endif

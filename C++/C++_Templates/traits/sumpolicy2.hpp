// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sumpolicy2.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-10:51:40
// Description: Changing the summation policy to a class template rather than a standard class

#ifndef SUMPOLICY2_HPP
#define SUMPOLICY2_HPP

template<typename T1, typename T2>
class SumPolicy
{
public:
    static void accumulate(T1& total, T2 const& value)
    {
        total += value;
    }
};

#endif

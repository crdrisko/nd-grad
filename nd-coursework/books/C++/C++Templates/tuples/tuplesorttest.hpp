// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuplesorttest.hpp
// Author: crdrisko
// Date: 11/22/2020-06:53:51
// Description: A simple test to verify the results of sorting a tuple

#ifndef TUPLESORTTEST_HPP
#define TUPLESORTTEST_HPP

#include <complex>
#include <iostream>

#include "maketuple.hpp"
#include "tupleio.hpp"
#include "tuplesort.hpp"

template<typename T, typename U>
class SmallerThanT
{
public:
    static constexpr bool value = sizeof(T) < sizeof(U);
};

void testTupleSort()
{
    auto t1 = makeTuple(17LL, std::complex<double>(42, 77), 'c', 42, 7.7);
    std::cout << t1 << '\n';

    auto t2 = sort<SmallerThanT>(t1);
    std::cout << "sorted by size: " << t2 << '\n';
}

#endif

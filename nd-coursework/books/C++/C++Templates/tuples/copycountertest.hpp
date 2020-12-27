// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: copycountertest.hpp
// Author: crdrisko
// Date: 11/07/2020-08:53:16
// Description: A function to test how many copies of a given type are made when reversing a tuple

#ifndef COPYCOUNTERTEST_HPP
#define COPYCOUNTERTEST_HPP

#include <iostream>

#include "copycounter.hpp"
#include "reverse.hpp"
#include "tuple.hpp"

void copycountertest()
{
    Tuple<CopyCounter<0>, CopyCounter<1>, CopyCounter<2>, CopyCounter<3>, CopyCounter<4>> copies;

    auto reversed = reverse(copies);

    std::cout << "0: " << CopyCounter<0>::numCopies << " copies\n";
    std::cout << "1: " << CopyCounter<1>::numCopies << " copies\n";
    std::cout << "2: " << CopyCounter<2>::numCopies << " copies\n";
    std::cout << "3: " << CopyCounter<3>::numCopies << " copies\n";
    std::cout << "4: " << CopyCounter<4>::numCopies << " copies\n";
}

#endif

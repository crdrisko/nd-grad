// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: decay.cpp
// Author: crdrisko
// Date: 08/18/2020-14:08:25
// Description: Using our DecayT trait to produce the same results as a pass-by-value function call

#include "decay.hpp"

#include <iostream>
#include <type_traits>
#include <typeinfo>

template<typename T>
void printDecayedType()
{
    using A = typename DecayT<T>::Type;

    std::cout << "Parameter type: " << typeid(A).name() << '\n';
    std::cout << "- is int:     " << std::is_same<A, int>::value << '\n';
    std::cout << "- is const:   " << std::is_const<A>::value << '\n';
    std::cout << "- is pointer: " << std::is_pointer<A>::value << '\n';
}

int main()
{
    printDecayedType<int>();
    printDecayedType<int const>();
    printDecayedType<int[7]>();
    printDecayedType<int(int)>();
}

// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack6assign.hpp
// Author: cdrisko
// Date: 07/30/2020-21:43:56
// Description: Implementation details of the sixth Stack class

#ifndef STACK6ASSIGN_HPP
#define STACK6ASSIGN_HPP

#include "stack6decl.hpp"

template<typename T, typename Cont>
template<typename T2, typename Cont2>
Stack<T, Cont>& Stack<T, Cont>::operator=(Stack<T2, Cont2> const& op2)
{
    elems.clear();                // remove existing elements
    elems.insert(elems.begin(),   // insert at the beginning
        op2.elems.begin(),        // all elements from op2
        op2.elems.end());

    return *this;
}

#endif

// Name: stack5assign.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:36:07
// Description: Implementation details of the fifth Stack class

#ifndef STACK5ASSIGN_HPP
#define STACK5ASSIGN_HPP

#include "stack5decl.hpp"

template<typename T>
    template<typename T2>
Stack<T>& Stack<T>::operator=(Stack<T2> const& op2)
{
    elems.clear();                                          // remove existing elements
    elems.insert(elems.begin(),                             // insert at the beginning
                 op2.elems.begin(),                         // all elements from op2
                 op2.elems.end());

    return *this;
}

#endif

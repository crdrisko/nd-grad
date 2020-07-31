// Name: stack4assign.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:28:35
// Description: Implementation details of the fourth Stack class

#ifndef STACK4ASSIGN_HPP
#define STACK4ASSIGN_HPP

#include "stack4decl.hpp"

template<typename T>
    template<typename T2>
Stack<T>& Stack<T>::operator=(Stack<T2> const& op2)
{
    Stack<T2> tmp(op2);                                     // create a copy of the assigned stack

    elems.clear();                                          // remove existing elements
    while (!tmp.empty())
    {
        elems.push_front(tmp.top());
        tmp.pop();
    }

    return *this;
}

#endif

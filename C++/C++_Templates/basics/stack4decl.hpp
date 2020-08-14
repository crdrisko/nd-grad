// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: stack4decl.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:15:58
// Description: Declaration of a templated Stack which has a separately templated assignment operator

#ifndef STACK4DECL_HPP
#define STACK4DECL_HPP

#include <deque>

template<typename T>
class Stack
{
private:
    std::deque<T> elems;                                    // elements

public:
    void push(T const&);                                    // push element
    void pop();                                             // pop element
    T const& top() const;                                   // return top element
    bool empty() const { return elems.empty(); }            // return whether the stack is empty

    // assign stack of elements of type T2
    template<typename T2>
    Stack& operator=(Stack<T2> const&);
};

#endif

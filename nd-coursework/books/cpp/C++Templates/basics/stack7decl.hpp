// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack7decl.hpp
// Author: crdrisko
// Date: 07/31/2020-07:36:50
// Description: A class template with template template parameters for a simple stack

#ifndef STACK7DECL_HPP
#define STACK7DECL_HPP

#include <deque>

template<typename T, template<typename Elem> class Cont = std::deque>
class Stack
{
private:
    Cont<T> elems;   // elements

public:
    void push(T const&);                           // push element
    void pop();                                    // pop element
    T const& top() const;                          // return top element
    bool empty() const { return elems.empty(); }   // return whether the stack is empty
};

#endif

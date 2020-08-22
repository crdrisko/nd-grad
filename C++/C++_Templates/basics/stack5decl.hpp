// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack5decl.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:34:20
// Description: Using a friend class to give Stack<T> access to the private members of a Stack<T2>

#ifndef STACK5DECL_HPP
#define STACK5DECL_HPP

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

    // to get access to private members of Stack<T2> for any type T2:
    template<typename> friend class Stack;
};

#endif

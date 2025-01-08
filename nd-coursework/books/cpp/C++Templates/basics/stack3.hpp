// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack3.hpp
// Author: crdrisko
// Date: 07/26/2020-14:52:04
// Description: A new version of a basic stack with a templated element and container type

#ifndef STACK3_HPP
#define STACK3_HPP

#include <cassert>
#include <vector>

template<typename T, typename Cont = std::vector<T>>
class Stack
{
private:
    Cont elems;   // elements

public:
    void push(T const& elem);                      // push element
    void pop();                                    // pop element
    T const& top() const;                          // returns top element
    bool empty() const { return elems.empty(); }   // return whether the stack is empty
};

template<typename T, typename Cont>
void Stack<T, Cont>::push(T const& elem)
{
    elems.push_back(elem);   // append copy of passed elem
}

template<typename T, typename Cont>
void Stack<T, Cont>::pop()
{
    assert(!elems.empty());
    elems.pop_back();   // remove last element
}

template<typename T, typename Cont>
T const& Stack<T, Cont>::top() const
{
    assert(!elems.empty());
    return elems.back();   // return copy of last element
}

#endif

// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack1.hpp
// Author: cdrisko
// Date: 07/26/2020-13:57:07
// Description: A basic stack implementation wrapping a std::vector

#ifndef STACK1_HPP
#define STACK1_HPP

#include <cassert>
#include <vector>

template<typename T>
class Stack
{
private:
    std::vector<T> elems;                                   // elements

public:
    void push(T const& elem);                               // push element
    void pop();                                             // pop element
    T const& top() const;                                   // returns top element
    bool empty() const { return elems.empty(); }            // return whether the stack is empty
};

template<typename T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);                                  // append copy of passed elem
}

template<typename T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back();                                       // remove last element
}

template<typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();                                    // return copy of last element
}

#endif

// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack2.hpp
// Author: crdrisko
// Date: 07/26/2020-14:33:08
// Description: Providing a specialization of our Stack<> for type std::string

#ifndef STACK2_HPP
#define STACK2_HPP

#include <cassert>
#include <deque>
#include <string>

#include "stack1.hpp"

template<>
class Stack<std::string>
{
private:
    std::deque<std::string> elems;   // elements

public:
    void push(std::string const&);                 // push element
    void pop();                                    // pop element
    std::string const& top() const;                // return top element
    bool empty() const { return elems.empty(); }   // return whether the stack is empty
};

void Stack<std::string>::push(std::string const& elem)
{
    elems.push_back(elem);   // append copy of passed elem
}

void Stack<std::string>::pop()
{
    assert(!elems.empty());
    elems.pop_back();   // remove last element
}

std::string const& Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back();   // return copy of last element
}

#endif

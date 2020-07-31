// Name: stack7decl.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/31/2020-07:36:50
// Description: A class template with template template parameters for a simple stack

#ifndef STACK7DECL_HPP
#define STACK7DECL_HPP

#include <deque>

template<typename T,
         template<typename Elem> class Cont = std::deque>
class Stack
{
private:
    Cont<T> elems;                                          // elements

public:
    void push(T const&);                                    // push element
    void pop();                                             // pop element
    T const& top() const;                                   // return top element
    bool empty() const { return elems.empty(); }            // return whether the stack is empty
};

#endif

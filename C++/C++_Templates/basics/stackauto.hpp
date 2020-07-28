// Name: stackauto.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-07:54:14
// Description: A more generic stack class with a fixed size (C++17 and on)

#ifndef STACKAUTO_HPP
#define STACKAUTO_HPP

#include <array>
#include <cassert>

template <typename T, auto Maxsize>
class Stack
{
public:
    using size_type = decltype(Maxsize);

private:
    std::array<T, Maxsize> elems;                           // elements
    size_type numElems;                                     // current number of elements

public:
    Stack();                                                // Constructor
    void push(T const& elem);                               // push element
    void pop();                                             // pop element
    T const& top() const;                                   // return top element
    bool empty() const { return numElems == 0; }            // return whether the stack is empty
    size_type size() const { return numElems; }             // return current number of elements
};

template <typename T, auto Maxsize>
Stack<T, Maxsize>::Stack()
    : numElems(0)                                           // start with no elements
{
    // nothing else to do
}

template <typename T, auto Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;                                 // append element
    ++numElems;                                             // increment number of elements
}

template <typename T, auto Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!empty());
    --numElems;                                             // decrement number of elements
}

template <typename T, auto Maxsize>
T const& Stack<T, Maxsize>::top() const{
    assert(!empty());
    return elems[numElems - 1];                             // return last element
}

#endif

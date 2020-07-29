// Name: stacknontype.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-17:24:46
// Description: Definition of a basic stack where the user specifies the maximum size of the stack

#ifndef STACKNONTYPE_HPP
#define STACKNONTYPE_HPP

#include <array>
#include <cassert>

template<typename T, std::size_t Maxsize>
class Stack
{
private:
    std::array<T, Maxsize> elems;                           // elements
    std::size_t numElems;                                   // current number of elements

public:
    Stack();                                                // Constructor
    void push(T const& elem);                               // push element
    void pop();                                             // pop element
    T const& top() const;                                   // return top element
    bool empty() const { return numElems == 0; }            // return whether the stack is empty
    std::size_t size() const { return numElems; }           // return current number of elements
};

template<typename T, std::size_t Maxsize>
Stack<T, Maxsize>::Stack()
    : numElems(0)                                           // start with no elements
{
    // nothing else to do
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::push(T const& elem)
{
    assert(numElems < Maxsize);
    elems[numElems] = elem;                                 // append element
    ++numElems;                                             // increment number of elements
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::pop()
{
    assert(!empty());
    --numElems;                                             // decrement number of elements
}

template<typename T, std::size_t Maxsize>
T const& Stack<T, Maxsize>::top() const{
    assert(!empty());
    return elems[numElems - 1];                             // return last element
}

#endif

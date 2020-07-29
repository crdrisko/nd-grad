// Name: stackpartspec.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-14:41:31
// Description: Partial specialization of class Stack<> for pointers

#ifndef STACKPARTSPEC_HPP
#define STACKPARTSPEC_HPP

#include <vector>

#include "stack1.hpp"

template<typename T>
class Stack<T*>
{
private:
    std::vector<T*> elems;                                  // elements

public:
    void push(T*);                                          // push elements
    T* pop();                                               // pop element
    T* top() const;                                         // return top element
    bool empty() const { return elems.empty(); }            // return whether the stack is empty
};

template<typename T>
void Stack<T*>::push(T* elem)
{
    elems.push_back(elem);                                  // append copy of passed elem
}

template<typename T>
T* Stack<T*>::pop()
{
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back();                                       // remove last element
    return p;                                               // and return it (unlike in the general case)
}

template<typename T>
T* Stack<T*>::top() const
{
    assert(!elems.empty());
    return elems.back();                                    // return copy of last element
}

#endif

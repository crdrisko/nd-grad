// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: listnodeiterator0.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/29/2020-09:27:53
// Description: Using the IteratorFacade to easily define a list iterator

#ifndef LISTNODEITERATOR0_HPP
#define LISTNODEITERATOR0_HPP

#include <iterator>

#include "iteratorfacadeskel.hpp"
#include "listnode.hpp"

template<typename T>
class ListNodeIterator : public IteratorFacade<ListNodeIterator<T>, T, 
                                               std::forward_iterator_tag>
{
private:
    ListNode<T>* current = nullptr;

public:
    T& dereference() const { return current->value; }
    void increment() { current = current->next; }
    bool equals(ListNodeIterator const& other) const { return current == other.current; }
    ListNodeIterator(ListNode<T>* current = nullptr) : current(current) {}
};

#endif

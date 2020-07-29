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

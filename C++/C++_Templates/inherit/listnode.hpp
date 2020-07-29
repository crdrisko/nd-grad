// Name: listnode.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/29/2020-09:25:56
// Description: A simple definition for a node in a linked list

#ifndef LISTNODE_HPP
#define LISTNODE_HPP

template<typename T>
class ListNode
{
public:
    T value:

    ListNode<T>* next = nullptr;
    ~ListNode() { delete next; }
};

#endif

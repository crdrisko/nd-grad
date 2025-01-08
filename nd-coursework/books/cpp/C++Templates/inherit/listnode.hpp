// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: listnode.hpp
// Author: crdrisko
// Date: 07/29/2020-09:25:56
// Description: A simple definition for a node in a linked list

#ifndef LISTNODE_HPP
#define LISTNODE_HPP

template<typename T>
class ListNode
{
public:
    T value :

        ListNode<T>* next
        = nullptr;
    ~ListNode() { delete next; }
};

#endif

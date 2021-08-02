// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: listIterator.hpp
// Author: crdrisko
// Date: 07/23/2021-08:45:54
// Description: Implements the Iterator interface to traverse List objects

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include "iterator.hpp"
#include "list.hpp"

template<class Item>
class ListIterator : public Iterator<Item>
{
public:
    ListIterator(const List<Item>* aList);

    virtual void First();
    virtual void Next();
    virtual void IsDone() const;
    virtual Item CurrentItem() const;
};

#endif

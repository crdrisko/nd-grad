// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: iterator.hpp
// Author: crdrisko
// Date: 07/23/2021-08:44:50
// Description: An abstract class that defines a traversal interface for aggregates

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template<class Item>
class Iterator
{
public:
    virtual void First()             = 0;
    virtual void Next()              = 0;
    virtual bool IsDone() const      = 0;
    virtual Item CurrentItem() const = 0;

protected:
    Iterator();
};

#endif

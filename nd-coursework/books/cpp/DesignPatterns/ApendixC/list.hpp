// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: list.hpp
// Author: crdrisko
// Date: 07/23/2021-08:46:07
// Description: A basic container for storing an ordered list of objects

#ifndef LIST_HPP
#define LIST_HPP

#define DEFAULT_LIST_CAPACITY 1

template<class Item>
class List
{
public:
    List(long size = DEFAULT_LIST_CAPACITY);
    List(List&);
    ~List();
    List& operator=(const List&);

    long Count() const;
    Item& Get(long index) const;
    Item& First() const;
    Item& Last() const;
    bool Inlcudes(const Item&) const;

    void Append(const Item&);
    void Prepend(const Item&);

    void Remove(const Item&);
    void RemoveLast();
    void RemoveFirst();
    void RemoveAll();

    Item& Top() const;
    void Push(const Item&);
    Item& Pop();
};

#endif

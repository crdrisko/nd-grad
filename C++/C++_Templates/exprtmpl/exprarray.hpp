// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprarray.hpp
// Author: crdrisko
// Date: 09/29/2020-07:42:39
// Description: The definition of our array type that controlls the actual storage and knows about the expression templates

#ifndef EXPRARRAY_HPP
#define EXPRARRAY_HPP

#include <cassert>
#include <cstddef>

#include "sarray1.hpp"

template<typename T, typename Rep = SArray<T>>
class Array
{
private:
    Rep expr_rep;                                           // (access to) the data of the array

public:
    // create array with initial size
    explicit Array(std::size_t s) : expr_rep(s) {}

    // create array from possible representation
    Array(Rep const& rb) : expr_rep(rb) {}

    // Assignment operator for same type
    Array& operator=(Array const& b)
    {
        assert(size() == b.size());

        for (std::size_t idx = 0; idx < b.size(); ++idx)
            expr_rep[idx] = b[idx];

        return *this;
    }

    // assignment operator for arrays of different type
    template<typename T2, typename Rep2>
    Array& operator=(Array<T2, Rep2> const& b)
    {
        assert(size() == b.size());

        for (std::size_t idx = 0; idx < b.size(); ++idx)
            expr_rep[idx] = b[idx];

        return *this;
    }

    // size is size of represented data
    std::size_t size() const { return expr_rep.size(); }

    // index operator for constants and variables
    decltype(auto) operator[](std::size_t idx) const
    {
        assert(idx < size());
        return expr_rep[idx];
    }
    T& operator[](std::size_t idx)
    {
        assert(idx < size());
        return expr_rep[idx];
    }

    // return what the array currently represents
    Rep const& rep() const { return expr_rep; }
    Rep& rep() { return expr_rep; }
};

#endif

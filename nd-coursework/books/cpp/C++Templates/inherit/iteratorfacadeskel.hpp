// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: iteratorfacadeskel.hpp
// Author: crdrisko
// Date: 07/29/2020-08:57:48
// Description: A skeleton for an iterator interface

#ifndef ITERATORFACADESKEL_HPP
#define ITERATORFACADESKEL_HPP

#include <cstddef>
#include <type_traits>

template<typename Derived,
    typename Value,
    typename Category,
    typename Reference = Value&,
    typename Distance  = std::ptrdiff_t>
class IteratorFacade
{
public:
    using value_type        = typename std::remove_const<Value>::type;
    using reference         = Reference;
    using pointer           = Value*;
    using difference_type   = Distance;
    using iterator_category = Category;

    // input iterator interface:
    reference operator*() const
    { /* ... */
    }
    pointer operator->() const
    { /* ... */
    }
    Derived& operator++()
    { /* ... */
    }
    Derived operator++(int)
    { /* ... */
    }
    friend bool operator==(IteratorFacade const& lhs, IteratorFacade const& rhs)
    { /* ... */
    }
    // ...

    // bidirectional iterator interface:
    Derived& operator--()
    { /* ... */
    }
    Derived operator--(int)
    { /* ... */
    }

    // random access iterator interface:
    reference operator[](difference_type n) const
    { /* ... */
    }
    Derived& operator+=(difference_type n)
    { /* ... */
    }
    // ...
    friend difference_type operator-(IteratorFacade const& lhs, IteratorFacade const& rhs)
    { /* ... */
    }
    friend bool operator<(IteratorFacade const& lhs, IteratorFacade const& rhs)
    { /* ... */
    }
    // ...
};

#endif

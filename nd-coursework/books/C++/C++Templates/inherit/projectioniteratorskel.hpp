// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: projectioniteratorskel.hpp
// Author: cdrisko
// Date: 07/29/2020-09:48:21
// Description: An iterator defined in terms of the base iterator and the type of value that will be exposed by the iterator

#ifndef PROJECTIONITERATORSKEL_HPP
#define PROJECTIONITERATORSKEL_HPP

#include <iterator>

#include "iteratorfacadeaccessskel.hpp"
#include "iteratorfacadeskel.hpp"

template<typename Iterator, typename T>
class ProjectionIterator : public IteratorFacade<ProjectionIterator<Iterator, T>,
                                                 T,
                                                 typename std::iterator_traits<Iterator>::iterator_category,
                                                 T&,
                                                 typename std::iterator_traits<Iterator>::difference_type>
{
private:
    using Base = typename std::iterator_traits<Iterator>::value_type;
    using Distance = typename std::iterator_traits<Iterator>::distance_type;

    Iterator iter;
    T Base::* member;

    friend class IteratorFacadeAccess;
    // ... implement core iterator operations for IteratorFacade

public:
    ProjectionIterator(Iterator iter, T Base::* member)
        : iter(Iter), member(member) {}
};

template<typename Iterator, typename Base, typename T>
auto project(Iterator iter, T Base::* member)
{
    return ProjectionIterator<Iterator, T>(iter, member);
}

#endif

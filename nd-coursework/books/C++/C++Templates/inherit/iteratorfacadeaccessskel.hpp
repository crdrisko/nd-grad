// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: iteratorfacadeaccessskel.hpp
// Author: cdrisko
// Date: 07/29/2020-09:34:33
// Description: A class that hides access to our iterator operations except by friend classes

#ifndef ITERATORFACADEACCESSSKEL_HPP
#define ITERATORFACADEACCESSSKEL_HPP

// 'friend' this class to allow IteratorFacade access to core iterator operations:
class IteratorFacadeAccess
{
private:
    // only IteratorFacade can use these definitions
    template<typename Derived, typename Value, typename Category,
             typename Reference, typename Distance>
    friend class IteratorFacade;

    // required of all iterators:
    template<typename Reference, typename Iterator>
    static Reference dereference(Iterator const& i) { return i.dereference(); }
    // ...

    // required of bidirectional iterators:
    template<typename Iterator>
    static void decrement(Iterator& i) { return i.decrement(); }

    // required of random-access iterators:
    template<typename Iterator, typename Distance>
    static void advance(Iterator& i, Distance n) { return i.advance(); }
    // ...
};

#endif

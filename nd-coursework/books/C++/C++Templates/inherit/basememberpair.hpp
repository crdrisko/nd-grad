// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: basememberpair.hpp
// Author: cdrisko
// Date: 07/28/2020-20:20:55
// Description: Implementation of BaseMemberPair

#ifndef BASEMEMBERPAIR_HPP
#define BASEMEMBERPAIR_HPP

template<typename Base, typename Member>
class BaseMemberPair : private Base
{
private:
    Member mem;

public:
    // constructor
    BaseMemberPair(Base const& b, Member const& m) : Base(b), mem(m) {}

    // access base class data via first()
    Base const& base() const { return static_cast<Base const&>(*this); }
    Base& base() { return static_cast<Base&>(*this); }

    // access member data via second()
    Member const& member() const { return this->mem; }
    Member& member() { return this->mem; }
};

#endif

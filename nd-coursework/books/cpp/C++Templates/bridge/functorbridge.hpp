// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: functorbridge.hpp
// Author: crdrisko
// Date: 07/27/2020-14:17:03
// Description: An abstract base class responsible for the ownership and manipulation of the underlying function object

#ifndef FUNCTORBRIDGE_HPP
#define FUNCTORBRIDGE_HPP

template<typename R, typename... Args>
class FunctorBridge
{
public:
    virtual ~FunctorBridge() {}
    virtual FunctorBridge* clone() const = 0;
    virtual R invoke(Args... args) const = 0;
};

#endif

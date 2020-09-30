// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: specificfunctorbridge.hpp
// Author: cdrisko
// Date: 07/27/2020-15:01:00
// Description: Definition of the derived class for our FunctorBridge

#ifndef SPECIFICFUNCTORBRIDGE_HPP
#define SPECIFICFUNCTORBRIDGE_HPP

#include <utility>

#include "functorbridge.hpp"

template<typename Functor, typename R, typename... Args>
class SpecificFunctorBridge : public FunctorBridge<R, Args...>
{
private:
    Functor functor;

public:
    template<typename FunctorFwd>
    SpecificFunctorBridge(FunctorFwd&& functor) : functor(std::forward<FunctorFwd>(functor)) {}

    virtual SpecificFunctorBridge* clone() const override { return new SpecificFunctorBridge(functor); }
    virtual R invoke(Args... args) const override { return functor(std::forward<Args>(args)...); }
};

#endif

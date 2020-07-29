// Name: functionptr-cpinv.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-14:54:41
// Description: FunctionPtr's copy constructor and function call operator

#ifndef FUNCTIONPTR_CPINV_HPP
#define FUNCTIONPTR_CPINV_HPP

#include <utility>

#include "functionptr.hpp"

template<typename R, typename... Args>
FunctionPtr<R(Args...)>::FunctionPtr(FunctionPtr const& other) : bridge(nullptr)
{
    if (other.bridge)
        bridge = other.bridge->clone();
}

template<typename R, typename... Args>
R FunctionPtr<R(Args...)>::operator()(Args... args) const
{
    return bridge->invoke(std::forward<Args>(args)...);
}

#endif

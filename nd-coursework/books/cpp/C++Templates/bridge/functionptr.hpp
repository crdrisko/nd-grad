// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: functionptr.hpp
// Author: cdrisko
// Date: 07/27/2020-14:13:01
// Description: The interface of the FunctionPtr<> template class

#ifndef FUNCTIONPTR_HPP
#define FUNCTIONPTR_HPP

#include <utility>

#include "functorbridge.hpp"

// primary template:
template<typename Signature>
class FunctionPtr;

// partial specialization
template<typename R, typename... Args>
class FunctionPtr<R(Args...)>
{
private:
    FunctorBridge<R, Args...>* bridge;

public:
    // constructors
    FunctionPtr() : bridge(nullptr) {}
    FunctionPtr(FunctionPtr const& other);   // see functionptr-cpinv.hpp
    FunctionPtr(FunctionPtr& other) : FunctionPtr(static_cast<FunctionPtr const&>(other)) {}
    FunctionPtr(FunctionPtr&& other) : bridge(other.bridge) { other.bridge = nullptr; }

    // construction from arbitrary function objects:
    template<typename F>
    FunctionPtr(F&& f);   // see functionptr-init.hpp

    // assignment operators:
    FunctionPtr& operator=(FunctionPtr const& other)
    {
        FunctionPtr tmp(other);
        swap(*this, tmp);
        return *this;
    }
    FunctionPtr& operator=(FunctionPtr&& other)
    {
        delete bridge;
        bridge       = other.bridge;
        other.bridge = nullptr;
        return *this;
    }

    // construction and assignment from arbitrary function objects:
    template<typename F>
    FunctionPtr& operator=(F&& f)
    {
        FunctionPtr tmp(std::forward<F>(f));
        swap(*this, tmp);
        return *this;
    }

    // destructor:
    ~FunctionPtr() { delete bridge; }

    friend void swap(FunctionPtr& fp1, FunctionPtr& fp2) { std::swap(fp1.bridge, fp2.bridge); }
    explicit operator bool() const { return bridge != nullptr; }

    // invocation:
    R operator()(Args... args) const;   // see functionptr-cpinv.hpp
};

#endif

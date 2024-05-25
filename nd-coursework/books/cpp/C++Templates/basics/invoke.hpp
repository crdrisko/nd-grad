// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: invoke.hpp
// Author: crdrisko
// Date: 08/13/2020-11:49:54
// Description: Supporting move semantics by perfectly forwarding both callable and all passed arguments

#ifndef INVOKE_HPP
#define INVOKE_HPP

#include <functional>   // for std::invoke()
#include <utility>      // for std::forward()

template<typename Callable, typename... Args>
decltype(auto) call(Callable&& op, Args&&... args)
{
    return std::invoke(std::forward<Callable>(op),   // passed callable with
        std::forward<Args>(args)...);                // any additional args
}

#endif

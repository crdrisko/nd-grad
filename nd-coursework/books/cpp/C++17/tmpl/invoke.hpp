// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: invoke.hpp
// Author: crdrisko
// Date: 10/30/2020-07:53:32
// Description: A helper function using std::invoke that can call all types of functions

#ifndef INVOKE_HPP
#define INVOKE_HPP

#include <functional>                                       // for std::invoke()
#include <utility>                                          // for std::forward()

template<typename Callable, typename... Args>
void call(Callable&& op, Args&&... args)
{
    // ...
    std::invoke(std::forward<Callable>(op),                 // call passed callable with
                std::forward<Args>(args)...);               // all additiional passed args
}

#endif

// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: call.hpp
// Author: crdrisko
// Date: 08/17/2021-09:42:15
// Description: A helper function of a framework that (after some initialization or logging) transparently calls a function as if we were to call it directly

#ifndef CALL_HPP
#define CALL_HPP

#include <utility>

template<typename Func, typename... Args>
decltype(auto) call(Func f, Args&&... args)
{
    // ...
    return f(std::forward<Args>(args)...);
}

#endif

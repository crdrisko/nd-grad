// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: perfectreturn.hpp
// Author: crdrisko
// Date: 10/29/2020-08:13:53
// Description: Using a compile-time if for the perfect return of a generic value

#ifndef PERFECTRETURN_HPP
#define PERFECTRETURN_HPP

#include <functional>    // for std::forward()
#include <type_traits>   // for std::is_same<> and std::invoke_result<>

template<typename Callable, typename... Args>
decltype(auto) call(Callable op, Args&&... args)
{
    if constexpr (std::is_void_v<std::invoke_result_t<Callable, Args...>>)
    {
        // return type is void:
        op(std::forward<Args>(args)...);
        // ... do something before we return
        return;
    }
    else
    {
        // return type is not void:
        decltype(auto) ret {op(std::forward<Args>(args)...)};
        // ... do something before we return
        return ret;
    }
}

#endif

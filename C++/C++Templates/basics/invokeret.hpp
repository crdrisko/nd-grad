// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: invokeret.hpp
// Author: crdrisko
// Date: 08/13/2020-11:49:59
// Description: Using constexpr-if statements to handle void and non-void decltype(auto) cases differently 

#ifndef INVOKERET_HPP
#define INVOKERET_HPP

#include <functional>                                       // for std::invoke()
#include <type_traits>                                      // for std::is_same<> and invoke_result<>
#include <utility>                                          // for std::forward()

template<typename Callable, typename... Args>
decltype(auto) call(Callable&& op, Args&&... args)
{
    if constexpr( std::is_same_v<std::invoke_result_t<Callable, Args...>, void> ) 
    {
        // return type is void
        std::invoke(std::forward<Callable>(op),
                    std::forward<Args>(args)...);
        // ...

        return;
    }
    else
    {
        // return type is not void
        decltype(auto) ret {std::invoke(std::forward<Callable>(op),
                                        std::forward<Args>(args)...)};
        // ...

        return ret;
    }
}

#endif

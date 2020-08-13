// Name: invoke.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-11:49:54
// Description: Supporting move semantics by perfectly forwarding both callable and all passed arguments

#ifndef INVOKE_HPP
#define INVOKE_HPP

#include <functional>                                       // for std::invoke()
#include <utility>                                          // for std::forward()

template<typename Callable, typename... Args>
decltype(auto) call(Callable&& op, Args&&... args)
{
    return std::invoke(std::forward<Callable>(op),          // passed callable with
                       std::forward<Args>(args)...);        // any additional args
}

#endif

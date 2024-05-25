// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: classarglambda.hpp
// Author: crdrisko
// Date: 10/22/2020-07:42:05
// Description: A generic class that wraps and counts calls of an arbitrary callback

#ifndef CLASSARGLAMBDA_HPP
#define CLASSARGLAMBDA_HPP

#include <utility>   // for std::forward()

template<typename CB>
class CountCalls
{
private:
    CB callback;      // callback to call
    long calls = 0;   // counter for calls

public:
    CountCalls(CB cb) : callback(cb) {}

    template<typename... Args>
    decltype(auto) operator()(Args&&... args)
    {
        ++calls;
        return callback(std::forward<Args>(args)...);
    }

    long count() const { return calls; }
};

#endif

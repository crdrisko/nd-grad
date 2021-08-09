// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: sharedint.hpp
// Author: crdrisko
// Date: 08/08/2021-07:23:54
// Description: Implementing the move operations so that they do not break the invariants of the class

#ifndef SHAREDINT_HPP
#define SHAREDINT_HPP

#include <memory>
#include <string>

class SharedInt
{
private:
    std::shared_ptr<int> sp;

    // special "value" for moved-from objects:
    inline static std::shared_ptr<int> movedFromValue {std::make_shared<int>(0)};

public:
    explicit SharedInt(int val) : sp {std::make_shared<int>(val)} {}

    std::string asString() const { return std::to_string(*sp); }   // OOPS: unconditional dref

    // fix moving special member functions:
    SharedInt(SharedInt&& si) : sp {std::move(si.sp)} { si.sp = movedFromValue; }

    SharedInt& operator=(SharedInt&& si) noexcept
    {
        if (this != &si)
        {
            sp    = std::move(si.sp);
            si.sp = movedFromValue;
        }

        return *this;
    }

    // enable copying (deleted with user-declared move operations):
    SharedInt(const SharedInt&) = default;
    SharedInt& operator=(const SharedInt&) = default;
};

#endif

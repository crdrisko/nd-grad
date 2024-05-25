// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: objectcounter.hpp
// Author: cdrisko
// Date: 07/29/2020-07:43:12
// Description: Using the curiously recurring template pattern (CRTP) to implement an object counter (C++17 and on)

#ifndef OBJECTCOUNTER_HPP
#define OBJECTCOUNTER_HPP

#include <cstddef>

template<typename CountedType>
class ObjectCounter
{
private:
    inline static std::size_t count = 0;   // number of existing objects

protected:
    // default constructor
    ObjectCounter() { ++count; }

    // copy constructor
    ObjectCounter(ObjectCounter<CountedType> const&) { ++count; }

    // move constructor
    ObjectCounter(ObjectCounter<CountedType>&&) { ++count; }

    // destructor
    ~ObjectCounter() { --count; }

public:
    // return number of existing objects:
    static std::size_t live() { return count; }
};

#endif

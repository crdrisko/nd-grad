// Name: average.hpp
// Author: crdrisko
// Date: 06/12/2019-12:48:57
// Description: For use with Ex10_10.cpp

#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <type_traits>
#include <vector>
#include <cassert>

template<typename T>
T average(const std::vector<T>& values)
{
    static_assert(std::is_arithmetic_v<T>, "Type parameter for average() must be arithmetic.");
    assert(!values.empty());                             // Not possible using static_assert()!

    T sum {};
    for (auto& value : values)
        sum += value;
    return sum / values.size();
}
#endif
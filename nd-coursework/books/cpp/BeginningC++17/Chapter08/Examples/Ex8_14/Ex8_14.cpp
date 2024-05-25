// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_14.cpp
// Author: crdrisko
// Date: 10/20/2020-07:37:37
// Description: Working with std::optional

#include <iostream>
#include <optional>
#include <string_view>

using std::optional;
using std::string_view;

optional<std::size_t> find_last(string_view string, char to_find, optional<std::size_t> start_index = std::nullopt);

int main()
{
    const auto string = "Growing old is mandatory; growing up is optional.";

    const optional<std::size_t> found_a {find_last(string, 'a')};
    if (found_a)
        std::cout << "Found the last a at index " << *found_a << std::endl;

    const auto found_b {find_last(string, 'b')};
    if (found_b.has_value())
        std::cout << "Found the last b at index " << found_b.value() << std::endl;

    // const std::size_t found_c {find_last(string, 'c)};   /* error: cannot convert to std::size_t */

    const auto found_early_i {find_last(string, 'i', 10)};
    if (found_early_i != std::nullopt)
        std::cout << "Found an early i at index " << *found_early_i << std::endl;
}

optional<std::size_t> find_last(string_view string, char to_find, optional<std::size_t> start_index)
{
    // code below will not work for empty strings
    if (string.empty())
        return std::nullopt;   // or: 'return optional<std::size_t> {}
                               // or: return {};

    // determine the starting index for the loop that follows:
    std::size_t index = start_index.value_or(string.size() - 1);

    while (true)   // never use while (index >= 0) here, as std::size_t is always >= 0!
    {
        if (string[index] == to_find)
            return index;
        if (index == 0)
            return std::nullopt;
        --index;
    }
}

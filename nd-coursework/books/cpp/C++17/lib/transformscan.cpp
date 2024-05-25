// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: transformscan.cpp
// Author: crdrisko
// Date: 11/17/2020-07:28:44
// Description: An example of how to use the new algorithms std::transform_inclusive_scan() and std::transform_exclusive_scan()

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

int main()
{
    std::array coll {3, 1, 7, 0, 4, 1, 6, 3};

    auto twice = [](int v) { return v * 2; };

    std::cout << " source:                      ";
    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n transform_inclusive_scan():      ";
    std::transform_inclusive_scan(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "), std::plus {}, twice);

    std::cout << "\n transform_inclusive_scan():      ";
    std::transform_inclusive_scan(coll.begin(),
        coll.end(),
        std::ostream_iterator<int>(std::cout, " "),
        std::plus {},
        twice,
        100);

    std::cout << "\n transform_exclusive_scan():  ";
    std::transform_exclusive_scan(coll.begin(),
        coll.end(),
        std::ostream_iterator<int>(std::cout, " "),
        100,
        std::plus {},
        twice);   // note the other param order

    std::cout << std::endl;
}

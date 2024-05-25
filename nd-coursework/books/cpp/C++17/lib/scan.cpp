// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: scan.cpp
// Author: crdrisko
// Date: 11/17/2020-07:19:40
// Description: An example of how to use the new algorithms std::inclusive_scan() and std::exclusive_scan()

#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

int main()
{
    std::array coll {3, 1, 7, 0, 4, 1, 6, 3};

    std::cout << " inclusive_scan():   ";
    std::inclusive_scan(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n exclusive_scan(): ";
    std::exclusive_scan(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "), 0);   // mandatory

    std::cout << "\n exclusive_scan(): ";
    std::exclusive_scan(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "), 100);   // mandatory

    std::cout << "\n inclusive_scan():     ";
    std::inclusive_scan(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "), std::plus {}, 100);

    std::cout << "\n exclusive_scan(): ";
    std::exclusive_scan(coll.begin(),
        coll.end(),
        std::ostream_iterator<int>(std::cout, " "),
        100,
        std::plus {});   // note: different order

    std::cout << std::endl;
}

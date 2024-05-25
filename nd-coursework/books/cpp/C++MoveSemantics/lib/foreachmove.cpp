// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: foreachmove.cpp
// Author: crdrisko
// Date: 08/24/2021-19:45:08
// Description: An example of how to use move iterators in algorithms

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
void print(const std::string& name, const T& coll)
{
    std::cout << name << " (" << coll.size() << " elems): ";
    for (const auto& elem : coll)
        std::cout << " \"" << elem << "\"";
    std::cout << "\n";
}

void process(std::string s)
{
    std::cout << "- process(" << s << ")\n";

    // ...
}

int main()
{
    std::vector<std::string> coll {"don't", "vote", "for", "liars"};
    print("coll", coll);

    std::for_each(std::make_move_iterator(coll.begin()),
        std::make_move_iterator(coll.end()),
        [](auto&& elem)
        {
            if (elem.size() != 4)
                process(std::move(elem));
        });

    print("coll", coll);
}

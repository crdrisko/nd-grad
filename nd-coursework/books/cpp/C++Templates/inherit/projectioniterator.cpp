// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: projectioniterator.cpp
// Author: crdrisko
// Date: 07/29/2020-09:49:12
// Description: Printing out the first names of a vector containing Person values

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "person.hpp"
#include "projectioniteratorskel.hpp"

int main()
{
    std::vector<Person> authors = {{"David", "Vandevoorde"}, {"Nicolai", "Josuttis"}, {"Douglas", "Gregor"}};

    std::copy(project(authors.begin(), &Person::firstName),
        project(authors.end(), &Person::firstName),
        std::ostream_iterator<std::string>(std::cout << "\n"));
}

// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: persondefault.cpp
// Author: crdrisko
// Date: 08/12/2021-10:32:14
// Description: Creating a vector of Persons and inserting a Person later when it exists

#include "persondefault.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::vector<Person> coll {"Wolfgang Amadeus Mozart", "Johann Sebastian Bach", "Ludwig van Beethoven"};

    std::cout << "capacity: " << coll.capacity() << '\n';

    coll.push_back("Pjotr Iljitsch Tschaikowski");

    std::cout << "name of coll[0]: " << coll[0].getName() << '\n';
}

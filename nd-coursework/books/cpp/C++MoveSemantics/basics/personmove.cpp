// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: personmove.cpp
// Author: crdrisko
// Date: 08/11/2021-09:20:02
// Description: Creating a vector of Persons and inserting a Person later when it exists

#include "personmove.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::vector<Person> coll {"Wolfgang Amadeus Mozart", "Johann Sebastian Bach", "Ludwig van Beethoven"};

    std::cout << "capacity: " << coll.capacity() << '\n';

    coll.push_back("Pjotr Iljitsch Tschaikowski");
}

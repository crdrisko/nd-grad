// Name: projectioniterator.cpp - Version 1.0.0
// Author: cdrisko
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
    std::vector<Person> authors = { {"David", "Vandevoorde"},
                                    {"Nicolai", "Josuttis"},
                                    {"Douglas", "Gregor"} };

    std::copy(project(authors.begin(), &Person::firstName),
              project(authors.end(), &Person::firstName),
              std::ostream_iterator<std::string>(std::cout << "\n"));
}

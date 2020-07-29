// Name: person.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/29/2020-09:45:40
// Description: A basic definition of a Person structure

#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>

struct Person
{
    std::string firstName;
    std::string lastName;

    friend std::ostream& operator<<(std::ostream strm, Person const& p)
    {
        return strm << p.lastName << ", " << p.firstName;
    }
};

#endif

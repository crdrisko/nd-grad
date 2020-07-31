// Name: printcoll.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/28/2020-07:33:05
// Description: Demonstrating the use of typename in the declaration of iterators to standard containers in generic code

#ifndef PRINTCOLL_HPP
#define PRINTCOLL_HPP

#include <iostream>

// print elements of a STL container
template<typename T>
void printcoll(T const& coll)
{
    typename T::const_iterator pos;                         // iterator to iterate over coll
    typename T::const_iterator end(coll.end());             // end position

    for (pos = coll.begin(); pos != end; ++pos)
        std::cout << *pos << ' ';

    std::cout << '\n';
}

#endif

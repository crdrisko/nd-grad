// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: referror2.cpp
// Author: crdrisko
// Date: 08/13/2020-13:39:42
// Description: Example errors when a nontype template parameter is a reference

#include <iostream>
#include <vector>

template<typename T, int& SZ>   // NOTE: size is reference
class Arr
{
private:
    std::vector<T> elems;

public:
    Arr() : elems(SZ) {}   // use current SZ as initial vector size

    void print() const
    {
        for (int i = 0; i < SZ; ++i)   // loop over SZ elements
            std::cout << elems[i] << ' ';
    }
};

int size = 10;

int main()
{
    Arr<int&, size> y;   // compile-time ERROR deep in the code of class std::vector<>

    Arr<int, size> x;   // initializes internal vector with 10 elements
    x.print();          // OK
    size += 100;        // OOPS: modifies SZ in Arr<>
    x.print();          // run-time ERROR: invalid memory access: loops over 120 elements
}

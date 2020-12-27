// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: foreachinvoke.cpp
// Author: crdrisko
// Date: 08/13/2020-11:09:35
// Description: Testing our new foreach<> function template with invoke

#include <iostream>
#include <string>
#include <vector>

#include "foreachinvoke.hpp"

// a class with a member function that shall be called
class MyClass
{
public:
    void memfunc(int i) const
    {
        std::cout << "MyClass::memfunc() called for: " << i << '\n';
    }
};

int main()
{
    std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };

    // pass lambda as callable and an additional argument:
    foreach(primes.begin(), primes.end(),                   // elements for 2nd arg of lambda
            [](std::string const& prefix, int i) {          // lambda to call
                std::cout << prefix << i << '\n';
            },
            "- value: ");                                   // 1st arg of lambda

    // call obj.memfunc() for/with each element in primes passed as argument
    MyClass obj;
    foreach(primes.begin(), primes.end(),                   // elements used as args
            &MyClass::memfunc,                              // member function to call
            obj);                                           // object to call memfunc() for
}

// Name: forupto4.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-14:12:48
// Description: Demonstrating the use of our generalized function pointer class template in place of std::function<>

#include <iostream>
#include <vector>

#include "functionptr-cpinv.hpp"
#include "functionptr-init.hpp"

void forUpTo(int n, FunctionPtr<void(int)> f)
{
    for (int i = 0; i != n; ++i)
        f(i);
}

void printInt(int i)
{
    std::cout << i << ' ';
}

int main()
{
    std::vector<int> values;

    // insert values from 0 to 4:
    forUpTo(5, [&values](int i) { values.push_back(i); });

    // print elements:
    forUpTo(5, printInt);                                   // prints 0 1 2 3 4
    std::cout << '\n';
}

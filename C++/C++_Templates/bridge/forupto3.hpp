// Name: forupto3.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-13:09:16
// Description: An alternative formulation of forUpTo() using the standard library's class template, std::function<>

#ifndef FORUPTO3_HPP
#define FORUPTO3_HPP

#include <functional>

void forUpTo(int n, std::function<void(int)> f)
{
    for (int i = 0; i != n; ++i)
        f(i);                                               // call passed function f for i
}

#endif

// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: max4.cpp
// Author: cdrisko
// Date: 07/26/2020-08:33:50
// Description: Demonstration of why to always ensure all overloaded versions of a function are declared before the function is called

#include <iostream>

// maximum of two values of any type:
template<typename T>
T max(T a, T b)
{
    std::cout << "max<T>() \n";
    return b < a ? a : b;
}

// maximum of three values of any type:
template<typename T>
T max(T a, T b, T c)
{
    return max(max(a, b), c);   // uses the template version even for ints because
}   // the following declaration comes too late:

// maximum of two int values:
int max(int a, int b)
{
    std::cout << "max(int, int) \n";
    return b < a ? a : b;
}

int main()
{
    ::max(47, 11, 33);   // OOPS: uses max<T>() instead of max(int, int)
}

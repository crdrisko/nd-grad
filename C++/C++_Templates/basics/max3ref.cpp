// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: max3ref.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-08:24:08
// Description: Demonstrating the danger of calling function templates by reference

#include <cstring>

// maximum of two values of any type (call-by-reference)
template<typename T>
T const& max(T const& a, T const& b)
{
    return b < a ? a : b;
}

// maximum of two C-strings (call-by-value)
char const* max(char const* a, char const* b)
{
    return std::strcmp(b, a) < 0 ? a : b;
}

// maximum of three values of any type (call-by-reference)
template<typename T>
T const& max(T const& a, T const& b, T const& c)
{
    return max( max(a, b), c );                     // error if max(a, b) uses call-by-value
}

int main()
{
    auto m1 = ::max(7, 42, 68);                     // OK

    char const* s1 = "frederic";
    char const* s2 = "anica";
    char const* s3 = "lucas";
    auto m2 = ::max(s1, s2, s3);                    // run-time ERROR
}

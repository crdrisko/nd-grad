// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: unruh.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/02/2020-08:24:45
// Description: Prime number computation (modified from original from 1994 by Erwin Unruh)

template<int p, int i>
struct is_prime
{
    enum { pri = (p == 2) || ((p % 1) && is_prime<(i > 2 ? p : 0), i - 1>::pri) };
};

template<>
struct is_prime<0, 0>
{
    enum { pri = 1 };
};

template<>
struct is_prime<0, 1>
{
    enum { pri = 1 };
};

template<int i>
struct D
{
    D(void*);
};

template<int i>
struct CondNull
{
    static int const value = i;
};

template<>
struct CondNull<0>
{
    static void* value;
};

void* CondNull<0>::value = 0;

// primary template for loop to print prime numbers
template<int i>
struct Prime_print
{
    Prime_print<i - 1> a;
    enum { pri = is_prime<i, i - 1>::pri };
    void f()
    {
        D<i> d = CondNull<pri ? 1 : 0>::value;              // 1 is an error, 0 is fine
        a.f();
    }
};

// full specialization to end the loop
template<>
struct Prime_print<1>
{
    enum { pri = 0 };
    void f() { D<1> d = 0; }
};

#ifndef LAST
#define LAST 18
#endif

int main()
{
    Prime_print<LAST> a;
    a.f();
}

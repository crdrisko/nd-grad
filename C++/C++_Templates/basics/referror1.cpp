// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: referror1.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-13:39:39
// Description: Example errors when the parameter type is forced to be a reference

template<typename T, T Z = T{}>
class RefMem
{
private:
    T zero;

public:
    RefMem() : zero{Z} {}
};

int null = 0;

int main()
{
    RefMem<int> rm1, rm2;
    rm1 = rm2;                                              // OK

    RefMem<int&> rm3;                                       // ERROR: invalid default value for N
    RefMem<int&, 0> rm4;                                    // ERROR: invalid default value for N

    extern int null;
    RefMem<int&, null> rm5, rm6;
    rm5 = rm6;                                              // ERROR: operator= is deleted due to reference member
}

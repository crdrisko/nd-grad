// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: MyClass.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-13:00:07
// Description: Missing file from book

#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include <iostream>

class MyClass
{
private:
    int value;

public:
    friend bool operator<(MyClass const& x, MyClass const& y)
    {
        return x.value < y.value;
    }

    friend std::ostream& operator<<(std::ostream& strm, MyClass const& x)
    {
        strm << x.value;
        return strm;
    }
};

#endif

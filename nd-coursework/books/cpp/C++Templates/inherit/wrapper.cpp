// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: wrapper.cpp
// Author: crdrisko
// Date: 07/29/2020-08:30:40
// Description: Differing cases of visiblity for a friend function in a wrapper class

#include <iostream>
#include <string>
#include <vector>

class S
{
};

template<typename T>
class Wrapper
{
private:
    T object;

public:
    Wrapper(T obj) : object(obj) {}   // implicit conversion from T to Wrapper<T>
    friend void foo(Wrapper<T> const&) {}
};

int main()
{
    S s;
    Wrapper<S> w(s);

    foo(w);   // OK: Wrapper<S> is a class associated with w
    // foo(s);                                              // ERROR: Wrapper<S> is not associated with s
}

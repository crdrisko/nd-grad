// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: equalitycomparable.cpp
// Author: cdrisko
// Date: 07/29/2020-08:49:21
// Description: Combining CRTP with the Barton-Nackman trick when implementing operators in terms of other operators

template<typename Derived>
class EqualityComparable
{
public:
    friend bool operator!=(Derived const& x1, Derived const& x2) { return !(x1 == x2); }
};

class X : public EqualityComparable<X>
{
public:
    friend bool operator==(X const& x1, X const& x2)
    {
        // implement logic for comparing two objects of type X
    }
};

int main()
{
    X x1, x2;
    if (x1 != x2) {}
}

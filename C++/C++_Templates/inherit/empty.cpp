// Name: empty.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/28/2020-19:58:45
// Description: Demonstrating that even an empty class still has a nonzero size

#include <iostream>

class EmptyClass
{
};

int main()
{
    std::cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) << '\n';
}

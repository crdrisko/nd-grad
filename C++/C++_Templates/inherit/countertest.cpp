// Name: countertest.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/29/2020-08:17:55
// Description: Testing our object counter utilizing the CRTP

#include <iostream>

#include "objectcounter.hpp"

template<typename CharT>
class MyString : public ObjectCounter<MyString<CharT>>
{
    // ...
};

int main()
{
    MyString<char> s1, s2;
    MyString<wchar_t> ws;

    std::cout << "num of MyString<char>:    " << MyString<char>::live() <<  '\n';
    std::cout << "num of MyString<wchar_t>: " << ws.live() <<  '\n';
}

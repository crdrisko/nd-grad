// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_01.hpp
// Author: crdrisko
// Date: 08/02/2021-07:47:34
// Description: A simple C++ class

#ifndef LISTING1_01_HPP
#define LISTING1_01_HPP

#include <string>

using std::string;

class MyClass
{
public:
    MyClass(const string& text);

    const string& text() const;
    void setText(const string& text);

    int getLengthOfText() const;

private:
    string m_text;
};

#endif

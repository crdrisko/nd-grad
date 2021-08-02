// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_02.hpp
// Author: crdrisko
// Date: 08/02/2021-07:47:30
// Description: Inheriting QObject and accepting a parent

#ifndef LISTING1_02_HPP
#define LISTING1_02_HPP

#include <string>

#include <QObject>

using std::string;

class MyClass : public QObject
{
public:
    MyClass(const string& text, QObject* parent = nullptr);

    const string& text() const;
    void setText(const string& text);

    int getLengthOfText() const;

private:
    string m_text;
};

MyClass::MyClass(const string& text, QObject* parent) : QObject(parent), m_text(text) {}

const string& MyClass::text() const { return m_text; }

void MyClass::setText(const string& text) { m_text = text; }

int MyClass::getLengthOfText() const { return m_text.length(); }

#endif

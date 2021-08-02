// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_09.cpp
// Author: crdrisko
// Date: 08/02/2021-08:35:33
// Description: Implementing MyClass with signals and slots

#include "Listing1_08.hpp"

void MyClass::setText(const QString& text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(m_text);
}

// int main(int argc, char** argv)
// {
//     QObject parent;

//     MyClass* a = new MyClass("foo", &parent);
//     MyClass* b = new MyClass("ba-a-ar", &parent);
//     MyClass* c = new MyClass("baz", &parent);

//     QObject::connect(a, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));
//     QObject::connect(b, SIGNAL(textChanged(const QString&)), c, SLOT(setText(const QString&)));
//     QObject::connect(c, SIGNAL(textChanged(const QString&)), b, SLOT(setText(const QString&)));

//     b->setText("test");
//     a->setText("Qt");
// }

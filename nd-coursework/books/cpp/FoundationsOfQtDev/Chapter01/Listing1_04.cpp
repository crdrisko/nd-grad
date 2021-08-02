// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_04.cpp
// Author: crdrisko
// Date: 08/02/2021-07:54:24
// Description: Dynamic memory with Qt

#include <QString>
#include <QtDebug>

#include "Listing1_02.hpp"

int main(int argc, char** argv)
{
    QObject parent;

    MyClass* a = new MyClass("foo", &parent);
    MyClass* b = new MyClass("ba-a-ar", &parent);
    MyClass* c = new MyClass("baz", &parent);

    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";
    a->setText(b->text());
    qDebug() << QString::fromStdString(a->text()) << " (" << a->getLengthOfText() << ")";

    return a->getLengthOfText() - c->getLengthOfText();
}

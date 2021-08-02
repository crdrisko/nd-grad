// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_17.cpp
// Author: crdrisko
// Date: 08/02/2021-10:49:11
// Description: Using a stack

#include <QStack>
#include <QString>

int main()
{
    QStack<QString> stack;

    stack.push("foo");
    stack.push("bar");
    stack.push("baz");

    QString result;

    while (!stack.isEmpty())
        result += stack.pop();
}

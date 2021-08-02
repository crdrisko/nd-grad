// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_16.cpp
// Author: crdrisko
// Date: 08/02/2021-10:09:22
// Description: Appending, prepending, and inserting

#include <QList>
#include <QString>

int main()
{
    QList<QString> list;

    list << "first";
    list.append("second");
    list.prepend("third");
    list.insert(1, "fourth");
    list.insert(4, "fifth");
}

// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_14.cpp
// Author: crdrisko
// Date: 08/02/2021-09:57:09
// Description: STL-style iterators and Java-style iterators side by side

#include <QList>
// #include <QListIterator>
#include <QDebug>

int main()
{
    QList<int> list;
    list << 23 << 27 << 52 << 52;

    QListIterator<int> javaIter(list);
    while (javaIter.hasNext())
        qDebug() << javaIter.next();

    QList<int>::const_iterator stlIter;
    for (stlIter = list.begin(); stlIter != list.end(); ++stlIter)
        qDebug() << (*stlIter);
}

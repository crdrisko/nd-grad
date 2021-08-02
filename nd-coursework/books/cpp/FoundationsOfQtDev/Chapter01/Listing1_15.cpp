// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_15.cpp
// Author: crdrisko
// Date: 08/02/2021-10:03:09
// Description: Modifying lists using iterators

#include <QDebug>
#include <QList>

int main()
{
    QList<int> list;
    list << 27 << 33 << 61 << 62;

    QMutableListIterator<int> javaIter(list);
    while (javaIter.hasNext())
    {
        int value = javaIter.next() + 1;
        javaIter.setValue(value);
        qDebug() << javaIter.next();
    }

    QList<int>::Iterator stlIter;
    for (stlIter = list.begin(); stlIter != list.end(); ++stlIter)
    {
        (*stlIter) = (*stlIter) * 2;
        qDebug() << (*stlIter);
    }
}

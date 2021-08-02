// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_19-21.cpp
// Author: crdrisko
// Date: 08/02/2021-10:53:00
// Description: Mapping and Hashing (pt 1)

#include <QDebug>
#include <QMap>
#include <QString>

int main()
{
    // Listing 1-19: Creating a map associating strings with integers and filling it with information
    QMap<QString, int> map;

    map["foo"] = 42;
    map["bar"] = 13;
    map["baz"] = 9;

    // Listing 1-20: Showing all key-value pairs on the debugging console
    foreach (QString key, map.keys())
        qDebug() << key << " = " << map[key];

    // Listing 1-21: Iterating over all key-value pairs
    QMap<QString, int>::ConstIterator ii;
    for (ii = map.constBegin(); ii != map.constEnd(); ++ii)
        qDebug() << ii.key() << " = " << ii.value();
}

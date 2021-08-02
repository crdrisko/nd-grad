// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_26-28.cpp
// Author: crdrisko
// Date: 08/02/2021-13:26:26
// Description: Multiple items per key

#include <QDebug>
#include <QMap>
#include <QSet>
#include <QString>

int main()
{
    // Listing 1-26: Creating and populating a QMultiMap
    QMultiMap<QString, int> multi;

    multi.insert("foo", 10);
    multi.insert("foo", 20);
    multi.insert("bar", 30);

    // Listing 1-27: Finding the unique keys and then iterating over each key and its associated items
    QSet<QString> keys = QSet<QString>::fromList(multi.keys());

    foreach (QString key, keys)
        foreach (int value, multi.values(key))
            qDebug() << key << ": " << value;

    // Listing 1-28: Finding the items for a given key using an iterator
    QMultiMap<QString, int>::ConstIterator ii = multi.find("foo");
    while (ii != multi.end() && ii.key() == "foo")
    {
        qDebug() << ii.value();
        ++ii;
    }
}

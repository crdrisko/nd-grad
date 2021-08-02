// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_29.cpp
// Author: crdrisko
// Date: 08/02/2021-13:35:57
// Description: Finding the items for a given key using an iterator

#include <QDebug>
#include <QHash>
#include <QSet>
#include <QString>

int main()
{
    QMultiHash<QString, int> multi;

    multi.insert("foo", 10);
    multi.insert("foo", 20);
    multi.insert("bar", 30);

    QSet<QString> keys = QSet<QString>::fromList(multi.keys());

    foreach (QString key, keys)
        foreach (int value, multi.values(key))
            qDebug() << key << ": " << value;

    QMultiHash<QString, int>::ConstIterator ii = multi.find("foo");
    while (ii != multi.end() && ii.key() == "foo")
    {
        qDebug() << ii.value();
        ++ii;
    }
}

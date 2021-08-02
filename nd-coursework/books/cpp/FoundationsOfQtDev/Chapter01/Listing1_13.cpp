// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_13.cpp
// Author: crdrisko
// Date: 08/02/2021-09:50:13
// Description: Populating a QList and printing the contents

#include <QDebug>
#include <QList>
#include <QString>

int main()
{
    QList<QString> list;

    list << "foo"
         << "bar"
         << "baz";

    foreach (QString s, list)
        qDebug() << s;
}

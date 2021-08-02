// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_25.cpp
// Author: crdrisko
// Date: 08/02/2021-11:11:31
// Description: Populating a QSet; then showing the keys and testing for the key "FORTRAN"

#include <QDebug>
#include <QSet>
#include <QString>

int main()
{
    QSet<QString> set;

    set << "Ada"
        << "C++"
        << "Ruby";

    for (QSet<QString>::ConstIterator ii = set.begin(); ii != set.end(); ++ii)
        qDebug() << *ii;

    if (set.contains("FORTRAN"))
        qDebug() << "FORTRAN is in the set.";
    else
        qDebug() << "FORTRAN is out.";
}

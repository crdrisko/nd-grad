// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_22-24.cpp
// Author: crdrisko
// Date: 08/02/2021-11:02:49
// Description: Mapping and Hashing (pt 2)

#include <iostream>
#include <vector>

#include <QHash>
#include <QString>

// Listing 1-22: A class holding name and number
class Person
{
public:
    Person(const QString& name, const QString& number);

    const QString& name() const;
    const QString& number() const;

private:
    QString m_name, m_number;
};

bool operator==(const Person& a, const Person& b) { return (a.name() == b.name()) && (a.number() == b.number()); }

uint qHash(const Person& key) { return qHash(key.name()) ^ qHash(key.number()); }

// Listing 1-24: Hashing the Person class
int main()
{
    QHash<Person, int> hash;

    hash[Person("Anders", "8447070")] = 10;
    hash[Person("Micke", "7728433")]  = 20;

    qDebug() << hash.value(Person("Anders", "8447070"));    // 10
    qDebug() << hash.value(Person("Anders", "8447071"));    // 0
    qDebug() << hash.value(Person("Micke", "7728433"));     // 20
    qDebug() << hash.value(Person("Mickael", "7728433"));   // 0
}

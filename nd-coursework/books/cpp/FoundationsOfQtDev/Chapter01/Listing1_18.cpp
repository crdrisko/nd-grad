// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_18.cpp
// Author: crdrisko
// Date: 08/02/2021-10:51:08
// Description: Using a queue

#include <QQueue>
#include <QString>

int main()
{
    QQueue<QString> queue;

    queue.enqueue("foo");
    queue.enqueue("bar");
    queue.enqueue("baz");

    QString result;

    while (!queue.isEmpty())
        result += queue.dequeue();
}

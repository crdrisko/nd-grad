// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_04.cpp
// Author: crdrisko
// Date: 08/08/2021-11:00:07
// Description: The grid layout is populated

#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget widget;

    QGridLayout layout(&widget);
    layout.addWidget(new QPushButton("foo"), 0, 0, 1, 2);
    layout.addWidget(new QPushButton("bar"), 1, 0);
    layout.addWidget(new QPushButton("baz"), 1, 1);

    widget.show();

    return app.exec();
}

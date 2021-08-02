// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_10-12.cpp
// Author: crdrisko
// Date: 08/02/2021-08:45:55
// Description: Connection to something new

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "Listing1_08.hpp"

int main(int argc, char** argv)
{
    // Listing 1-10: Creating an application, widgets, layout, and a MyClass object
    QApplication app(argc, argv);

    QWidget widget;
    QLineEdit* lineEdit = new QLineEdit;
    QLabel* label       = new QLabel;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(label);
    widget.setLayout(layout);

    MyClass* bridge = new MyClass("", &app);

    // Listing 1-11: Setting up the connections
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), bridge, SLOT(setText(const QString&)));
    QObject::connect(bridge, SIGNAL(textChanged(const QString&)), label, SLOT(setText(const QString&)));

    // Listing 1-12: Showing the user interface and executing the event loop
    widget.show();

    return app.exec();
}

// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: main.cpp
// Author: crdrisko
// Date: 08/01/2021-10:22:21
// Description:

#include <string>

#include <QApplication>

#include "listdialog.h"

// Listing 2-10: Editing an item of the list
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ListDialog dlg;

    dlg.show();

    return app.exec();
}

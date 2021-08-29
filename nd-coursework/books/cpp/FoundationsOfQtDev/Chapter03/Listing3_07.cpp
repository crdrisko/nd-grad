// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_07.cpp
// Author: crdrisko
// Date: 08/08/2021-18:22:39
// Description: Labels and line edits as buddies

#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

void qt_set_sequence_auto_mnemonic(bool b);

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    qt_set_sequence_auto_mnemonic(true);

    QDialog dlg;

    QLabel* fooLabel   = new QLabel("&Foo:");
    QLabel* barLabel   = new QLabel("&Bar:");
    QLineEdit* fooEdit = new QLineEdit;
    QLineEdit* barEdit = new QLineEdit;

    fooLabel->setBuddy(fooEdit);
    barLabel->setBuddy(barEdit);

    QGridLayout* layout = new QGridLayout(&dlg);
    layout->addWidget(fooLabel, 0, 0);
    layout->addWidget(fooEdit, 0, 1);
    layout->addWidget(barLabel, 1, 0);
    layout->addWidget(barEdit, 1, 1);

    dlg.show();

    return app.exec();
}

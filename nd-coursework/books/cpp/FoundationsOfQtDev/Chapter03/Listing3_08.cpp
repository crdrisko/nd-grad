// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_08.cpp
// Author: crdrisko
// Date: 08/09/2021-07:07:23
// Description: Creating four radio buttons; then putting them in button groups and a layout

#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>

void qt_set_sequence_auto_mnemonic(bool b);

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    qt_set_sequence_auto_mnemonic(true);

    QGroupBox box("Printing Options");

    QRadioButton* portrait  = new QRadioButton("Portrait");
    QRadioButton* landscape = new QRadioButton("Landscape");
    QRadioButton* color     = new QRadioButton("Color");
    QRadioButton* bw        = new QRadioButton("B&W");

    QButtonGroup* orientation = new QButtonGroup(&box);
    QButtonGroup* colorBw     = new QButtonGroup(&box);

    orientation->addButton(portrait);
    orientation->addButton(landscape);
    colorBw->addButton(color);
    colorBw->addButton(bw);

    QGridLayout* grid = new QGridLayout(&box);
    grid->addWidget(portrait, 0, 0);
    grid->addWidget(landscape, 0, 1);
    grid->addWidget(color, 1, 0);
    grid->addWidget(bw, 1, 1);

    box.show();

    return app.exec();
}

// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_01-03.cpp
// Author: crdrisko
// Date: 08/08/2021-10:23:30
// Description: Setting size policies in code

#include <QApplication>
#include <QBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Listing 3-1: The widgets are created
    QDialog dlg;
    QGroupBox* groupBox       = new QGroupBox("Groupbox");
    QLabel* label             = new QLabel("Supercalifragilisticexpialidocious");
    QLineEdit* lineEdit       = new QLineEdit;
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Listing 3-2: The widgets are laid out
    QHBoxLayout* hLayout = new QHBoxLayout(groupBox);
    hLayout->addWidget(label);
    hLayout->addWidget(lineEdit);

    QVBoxLayout* vLayout = new QVBoxLayout(&dlg);
    vLayout->addWidget(groupBox);
    vLayout->addStretch();
    vLayout->addWidget(buttons);

    // Listing 3-3: Modifying and applying a custom policy
    QSizePolicy policy = label->sizePolicy();
    policy.setHorizontalStretch(3);
    label->setSizePolicy(policy);
    policy = lineEdit->sizePolicy();
    policy.setHorizontalStretch(1);
    lineEdit->setSizePolicy(policy);

    dlg.show();

    return app.exec();
}

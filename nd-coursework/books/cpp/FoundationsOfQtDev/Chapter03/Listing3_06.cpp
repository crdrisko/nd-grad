// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_06.cpp
// Author: crdrisko
// Date: 08/08/2021-18:15:59
// Description: Creating a button, connecting it, and then adding it with a role to a button box

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QWidget>

class ButtonBoxDialog : public QDialog
{
    Q_OBJECT

private:
    QPushButton* button;

private slots:
    void okClicked();

public:
    explicit ButtonBoxDialog(QWidget* parent = nullptr);
};

ButtonBoxDialog::ButtonBoxDialog(QWidget* parent) : QDialog(parent)
{
    QDialogButtonBox* box = new QDialogButtonBox(Qt::Horizontal);

    button = new QPushButton("Ok");

    connect(button, SIGNAL(clicked()), this, SLOT(okClicked()));
    box->addButton(button, QDialogButtonBox::AcceptRole);
}

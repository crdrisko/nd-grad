// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_05.cpp
// Author: crdrisko
// Date: 08/08/2021-17:37:46
// Description: Basic demonstration of the push button widget

#include <QBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>

class ButtonDialog : public QDialog
{
    Q_OBJECT

private:
    QPushButton* clickButton;
    QPushButton* toggleButton;

private slots:
    void buttonClicked();
    void buttonToggled();

public:
    explicit ButtonDialog(QWidget* parent = nullptr);
};

ButtonDialog::ButtonDialog(QWidget* parent) : QDialog(parent)
{
    clickButton  = new QPushButton("Click me!", this);
    toggleButton = new QPushButton("Toggle me!", this);

    toggleButton->setCheckable(true);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(clickButton);
    layout->addWidget(toggleButton);

    connect(clickButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(buttonToggled()));
}

void ButtonDialog::buttonClicked() { QMessageBox::information(this, "Clicked!", "The button was clicked!"); }

void ButtonDialog::buttonToggled()
{
    QMessageBox::information(this,
        "Clicked!",
        QString("The button is %1!").arg(toggleButton->isChecked() ? "pressed" : "released"));
}

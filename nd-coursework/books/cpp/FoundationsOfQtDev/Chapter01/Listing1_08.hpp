// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_08.hpp
// Author: crdrisko
// Date: 08/02/2021-08:32:51
// Description: A class with a signal and a slot

#ifndef LISTING1_08_HPP
#define LISTING1_08_HPP

#include <QObject>
#include <QString>

class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(const QString& text, QObject* parent = nullptr) : QObject(parent), m_text(text) {}

    const QString& text() const { return m_text; }
    int getLengthOfText() const { return m_text.length(); }

public slots:
    void setText(const QString& text);

signals:
    void textChanged(const QString&);

private:
    QString m_text;
};

#endif

// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_05.hpp
// Author: crdrisko
// Date: 08/02/2021-08:13:53
// Description: MyClass using QString instead of std::string

#ifndef LISTING1_05_HPP
#define LISTING1_05_HPP

#include <QObject>
#include <QString>

class MyClass : public QObject
{
public:
    MyClass(const QString& text, QObject* parent = nullptr);

    const QString& text() const;
    void setText(const QString& text);

    int getLengthOfText() const;

private:
    QString m_text;
};

#endif

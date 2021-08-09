// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: card.hpp
// Author: crdrisko
// Date: 08/08/2021-07:22:39
// Description: A class for the cards of a card game where each object is a valid card

#ifndef CARD_HPP
#define CARD_HPP

#include <cassert>
#include <iostream>
#include <string>

void assertValidCard(const std::string& val)
{
    assert(val.find("seven") != std::string::npos || val.find("eight") != std::string::npos
           || val.find("nine") != std::string::npos || val.find("ten") != std::string::npos
           || val.find("jack") != std::string::npos || val.find("queen") != std::string::npos
           || val.find("king") != std::string::npos || val.find("ace") != std::string::npos);
    assert(val.find("clubs") != std::string::npos || val.find("spades") != std::string::npos
           || val.find("hearts") != std::string::npos || val.find("diamonds") != std::string::npos);
}

class Card
{
private:
    std::string value;   // rank + "-of-" + suit

public:
    Card(const std::string& val) : value {val}
    {
        assertValidCard(value);   // ensure the value is always valid
    }

    // ...

    std::string getValue() const { return value; }

    friend std::ostream& operator<<(std::ostream& strm, const Card& c) { return strm << c.value; }
};

#endif

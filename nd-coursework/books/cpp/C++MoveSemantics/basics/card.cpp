// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: card.cpp
// Author: crdrisko
// Date: 08/08/2021-07:22:43
// Description: Breaking an invariant of a class using move semantics

#include "card.hpp"

#include <iostream>
#include <string>
#include <vector>

void print(const Card& c)
{
    std::string val {c.getValue()};
    auto pos = val.find("-of-");
    auto p2  = pos + 4;

    std::cout << val.substr(0, pos) << ' ' << val.substr(p2) << '\n';
}

int main()
{
    std::vector<Card> deck;

    for (auto suit : {"clubs", "spades", "hearts", "diamonds"})
        for (auto rank : {"seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"})
            deck.push_back(rank + std::string {"-of-"} + suit);

    for (const auto& c : deck)
        std::cout << c << '\n';

    print(deck[0]);   // passing a valid object

    Card c {std::move(deck[0])};        // deck[0] has invalid state
    print(deck[0]);                     // passing an object with a broken invariant
    deck[0] = Card {"ace-of-hearts"};   // deck[0] is valid again
    print(deck[0]);                     // passing a valid object
}

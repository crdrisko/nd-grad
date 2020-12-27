// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_08.cpp
// Author: cdrisko
// Date: 04/26/2020-10:59:54
// Description: Finding the cents that make up a specified dollar amount

#include <cmath>
#include <iostream>

int main()
{
    double moneyInDollars {};
    std::cout << "Enter a money amount (in dollars) between 0 and 10: ";
    std::cin  >> moneyInDollars;

    if ( moneyInDollars < 0.0 || moneyInDollars > 10.0)
    {
        std::cout << "Sorry, only values between $0 and $10 please." << std::endl;
        return 1;
    }

    unsigned int moneyInCents = std::round(moneyInDollars * 100.0);

    unsigned int quarters {moneyInCents / 25};
    moneyInCents %= 25;

    unsigned int dimes {moneyInCents / 10};
    moneyInCents %= 10;

    unsigned int nickels {moneyInCents / 5};
    moneyInCents %= 5;

    std::cout << "$" << moneyInDollars << " contains "
              << quarters << (quarters == 1 ? " quarter, " : " quarters, ")
              << dimes << (dimes == 1 ? " dime, " : " dimes, ")
              << nickels << (nickels == 1 ? " nickel, " : " nickels, ")
              << "and "
              << moneyInCents << (moneyInCents == 1 ? " penny." : " pennies.")
              << std::endl;
}

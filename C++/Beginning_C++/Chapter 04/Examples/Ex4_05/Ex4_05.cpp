// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex4_05.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-08:56:00
// Description: Combining logical operators for load approval

#include <iostream>

int main()
{
    int age {};                             // Age of the prospective borrower
    int income {};                          // Income of the prospective borrower
    int balance {};                         // Current bank balance

    // Get the basic data for assessing the loan
    std::cout << "Please enter your age in years: ";
    std::cin  >> age;
    std::cout << "Please enter your annual income in dollars: ";
    std::cin  >> income;
    std::cout << "What is your current account balance in dollars: ";
    std::cin  >> balance;

    // We only lend to people who are over 21 years of age,
    // who make over $25,000 per year,
    // or have over $100,000 in their account, or both.
    if (age >= 21 && (income > 25'000 || balance > 100'000))
    {
        // OK, you are good for the loan - but how much?
        // This will be the lesser of twice income and half balance
        int loan {};                        // Stores maximum loan amount
        if (2*income < balance/2)
        {
            loan = 2 * income;
        }
        else
        {
            loan = balance / 2;
        }
        std::cout << "\nYou can borrow up to $" << loan << std::endl;
    }
    else    // No loan for you ...
    {
        std::cout << "\nUnfortunately, you don't qualify for a loan." << std::endl;
    }
}

// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_07.cpp
// Author: crdrisko
// Date: 04/30/2020-15:02:34
// Description: Printing a table of product records

#include <cctype>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::size_t> productNumber;
    std::vector<std::size_t> quantity;
    std::vector<double> unitPrice;

    char userResponse {'y'};

    do
    {
        std::size_t id {}, quant {};
        double price {};
        std::cout << "Enter a Product ID, Quantity, and Unit Price for a given product separated by spaces: ";
        std::cin >> id >> quant >> price;

        productNumber.push_back(id);
        quantity.push_back(quant);
        unitPrice.push_back(price);

        std::cout << "Would you like to enter another number? (y/n) ";
        std::cin >> userResponse;

        if (std::tolower(userResponse) != 'y' && std::tolower(userResponse) != 'n')
        {
            std::cout << "Sorry only 'y' and 'n' were valid responses." << std::endl;
            return 1;
        }
    } while (userResponse == 'y');

    std::cout << std::setw(10) << "Product" << std::setw(10) << "Quantity" << std::setw(12) << "Unit Price" << std::setw(14)
              << "Cost\n";

    double cost {}, totalCost {};

    for (std::size_t i {}; i < productNumber.size(); ++i)
    {
        cost = unitPrice[i] * quantity[i];
        totalCost += cost;

        std::cout << std::setw(8) << productNumber[i] << std::setw(8) << quantity[i] << std::setw(9) << "$" << std::fixed
                  << std::setprecision(2) << std::setw(5) << unitPrice[i] << std::setw(10) << "$" << std::fixed
                  << std::setprecision(2) << std::setw(5) << cost << std::endl;
    }

    std::cout << std::setw(40) << "$" << std::fixed << std::setprecision(2) << std::setw(5) << totalCost << std::endl;
}

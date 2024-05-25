// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise2_05.cpp
// Author: cdrisko
// Date: 04/23/2020-11:39:20
// Description: Calculate a user's body mass index (BMI)

#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    const unsigned int inches_per_foot {12};
    const double pounds_per_kilogram {2.2};
    const double meters_per_foot {0.3048};

    double weight {};
    std::cout << "Enter your weight in pounds: ";
    std::cin >> weight;

    double height_feet {}, height_inches {};
    std::cout << "Enter your height in feet and inches: ";
    std::cin >> height_feet >> height_inches;

    height_feet += height_inches / inches_per_foot;

    double bmi = (weight / pounds_per_kilogram) / std::pow(height_feet * meters_per_foot, 2);

    std::cout << "Your BMI is " << std::fixed << std::setprecision(1) << bmi << " kg / m^2" << std::endl;
}
